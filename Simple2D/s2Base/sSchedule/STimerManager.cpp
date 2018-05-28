#include "STimerManager.h"
#include "STimer.h"
STimerManager *STimerManager::sm_pInstance = nullptr;
//取得实例
STimerManager *STimerManager::GetInstance()
{
    if (!sm_pInstance)
    {
        sm_pInstance = new STimerManager();
    }
    return sm_pInstance;
}

void STimerManager::DestroyInstance()
{
    if (sm_pInstance)
    {
        delete sm_pInstance;
    }
    sm_pInstance = nullptr;
}

//添加定时器
void STimerManager::AddTimer(STimer *pTimer)
{
    m_setTimers->insert(pTimer);
}
//移除定时器
void STimerManager::RemoveTimer(STimer *pTimer)
{
    m_setTimers->erase(pTimer);
}
void STimerManager::RemoveTimersAll()
{
    m_setTimers->clear();
}

//清理调度
void STimerManager::Purge()
{
    //XXX:不知道这个Set有什么用
    SwapPool();
    STimer *timer = nullptr;
    auto &it = m_setTimers->end();
    while(!m_pCurReleasePool->empty())
    {
        timer = m_pCurReleasePool->front();
        RemoveTimer(timer);
        delete timer;
        m_pCurReleasePool->pop();
    }
}

//销毁定时器
void STimerManager::DestroyTimer(STimer *pTimer)
{
    m_pCurBufferPool->push(pTimer);
}
void STimerManager::DestroyTimersAll()
{
    for(auto &it : *m_setTimers)
    {
        m_pCurBufferPool->push(it);
    }
}

STimerManager::STimerManager()
{
    m_setTimers = new std::unordered_set<STimer *>();
    m_pCurReleasePool = new S2TimerPool();
    m_pCurBufferPool= new S2TimerPool();

}
STimerManager::~STimerManager()
{
    delete m_pCurBufferPool;
    delete m_pCurReleasePool;
   
    delete m_setTimers;

}

void STimerManager::SwapPool()
{
    S2TimerPool *tmp=nullptr;
    tmp = m_pCurReleasePool;
    m_pCurReleasePool = m_pCurBufferPool;
    m_pCurBufferPool = tmp;
}