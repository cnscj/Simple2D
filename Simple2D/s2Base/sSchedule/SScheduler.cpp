#include "SScheduler.h"
#include <cmath>
#include <chrono>
SScheduler::SScheduler():
m_unTaskIds(0),m_fTimeScale(1.0f)
{
    m_dTimePoint = __GetTimeTick();
}
SScheduler::~SScheduler()
{
    RemoveAllTasks();
}

float  SScheduler::GetTimeScale(void)
{
    return m_fTimeScale;
}
void  SScheduler::SetTimeScale(float fTimeScale)
{
    m_fTimeScale = fTimeScale;
}

unsigned int SScheduler::AddTask(std::function<void()> func, double interval, double delay, int repeat)
{
    STask *pInfo = new STask();
    pInfo->lamEvent = func;
    pInfo->dInterval = interval;
    pInfo->dDelay = delay;
    pInfo->nTimes = repeat;
    pInfo->dNextTime = m_dTimePoint + interval;
    pInfo->dUsedTime = 10000 * m_fTimeScale;
    pInfo->bEnabled = true;
    pInfo->unFlag = 1;   //重排标记
    pInfo->unId = ++m_unTaskIds;
    
    m_setTasks.insert(pInfo);
    return m_unTaskIds;
}

void SScheduler::RemoveTask(unsigned int id, bool bRelease)
{
    auto &it = __GetTaskIterator(id);
    if(it != m_setTasks.end()) 
        m_queDirtyTasks.push(TaskIteratorPair((bRelease? 1 : 0), it));
}

void SScheduler::RemoveAllTasks(bool bRelease)
{
    for(auto &it = m_setTasks.begin();it != m_setTasks.end();)
        m_queDirtyTasks.push(TaskIteratorPair(bRelease ? 1 : 0, it));

}

bool SScheduler::IsTaskPaused(unsigned int id)
{
    auto &it = __GetTaskIterator(id);
    if(it != m_setTasks.end()) return !(*it)->bEnabled;
    return false;
}

void SScheduler::PauseTask(unsigned int id)
{
    auto &it = __GetTaskIterator(id);
    if(it != m_setTasks.end() ) (*it)->bEnabled = false;
}

void SScheduler::ResumeTask(unsigned int id)
{
    auto &it = __GetTaskIterator(id);
    if(it != m_setTasks.end()) (*it)->bEnabled = true;
}

//开始调度
void SScheduler::ScheduleAllTasks(float fDt)
{
    __OnPreSchedule(fDt);
    __OnScheduling(fDt);
    __OnAftSchedule(fDt);
}
//处理所有人物
void SScheduler::DealAllTasks(float fTimeScale)
{
    __OnPreSchedule(0);
    __OnScheduling();
    __OnAftSchedule(0);
}

void SScheduler::__OnPreSchedule(float fDt)
{
    //调整调度序列
    while (!m_queAddTasks.empty())
    {
        auto &it = m_queAddTasks.front();
        m_setTasks.insert(it);
        m_queAddTasks.pop();
    }
    
}
void SScheduler::__OnScheduling(float fDt)
{
    m_dTimePoint += (fDt * m_fTimeScale);
    
    //就绪态变为调度态
    auto iIt = m_setTasks.begin();
    auto task = (STask *)nullptr;
    double lastUsedTime;
    while(iIt != m_setTasks.end())
    {
        task = *iIt;
        if(m_dTimePoint >= (task->dNextTime + task->dDelay))
        {
            if(task->bEnabled)
            {
                task->lamEvent();
                //XXX:这里应该获得实际的耗时,且脏任务标记算法不是很好
                lastUsedTime = task->dUsedTime;
                task->dUsedTime = m_dTimePoint - (task->dNextTime + task->dDelay);
                task->dNextTime = m_dTimePoint + task->dInterval;
                task->unFlag = (::fabs(task->dUsedTime - lastUsedTime)>10 * m_fTimeScale) ? 1 : 0;
                --task->nTimes;  
            }
        }
        __CheckTask(iIt);
        ++iIt;
    }
}

void SScheduler::__OnScheduling()
{

    //就绪态变为调度态
    auto iIt = m_setTasks.begin();
    auto task = (STask *)nullptr;
    double currTimePoint;
    double currUseTime;
    while (iIt != m_setTasks.end())
    {
        //更新当前TimePoint
        m_dTimePoint = __GetTimeTick();
        task = *iIt;
        if (m_dTimePoint >= (task->dNextTime + task->dDelay))
        {
            if (task->bEnabled)
            {
                task->lamEvent();
                currTimePoint = __GetTimeTick();
                currUseTime = currTimePoint - m_dTimePoint;
                //XXX:脏任务标记算法不是很好
                task->unFlag = (::fabs(task->dUsedTime - currUseTime)>10 * m_fTimeScale) ? 1 : 0;
                task->dUsedTime = currUseTime;
                task->dNextTime = currTimePoint + task->dInterval;
                --task->nTimes;
            }
        }
        __CheckTask(iIt);
        ++iIt;
    }
}

//任务检查
bool SScheduler::__CheckTask(TaskSet::iterator &it)
{
    //送入垃圾坟墓
    auto task = *it;
    if( task->nTimes == 0 ){
        m_queDirtyTasks.push(TaskIteratorPair(1,it));
    }else{
        //一般为权值突变的任务
        if(task->unFlag == 1)
        {
            //加入标记队列
            m_queDirtyTasks.push(TaskIteratorPair(0,it));
            //重新插入
            m_queAddTasks.push(task);
            task->unFlag = 0;
        }
    }
    
    return true;
}

void SScheduler::__OnAftSchedule(float fDt)
{
    //脏任务处理
    while (!m_queDirtyTasks.empty())
    {
        auto &it = m_queDirtyTasks.front();

        if (it.first){
            delete (*it.second);
        }

        m_setTasks.erase(it.second);
        m_queDirtyTasks.pop();
    }

}
STask *SScheduler::__GetTask(unsigned int id)
{
    
    auto &it = __GetTaskIterator(id);
    if(it != m_setTasks.end())
        return *it;
    return nullptr;
}

SScheduler::TaskSet::iterator SScheduler::__GetTaskIterator(unsigned int id)
{
    for (auto &it = m_setTasks.begin(); it != m_setTasks.end();++it)
    {
        if ((*it)->unId == id)
            return it;
    }
    return m_setTasks.end();
}

//销毁任务
void SScheduler::__DestroyTask(unsigned int id)
{
    auto &it = __GetTaskIterator(id);
    m_setTasks.erase(it);
}

//取得时间戳
double SScheduler::__GetTimeTick()
{
    //化为单位s
    return (double)(std::chrono::high_resolution_clock::now().time_since_epoch().count())/10000000.0f * m_fTimeScale;
}