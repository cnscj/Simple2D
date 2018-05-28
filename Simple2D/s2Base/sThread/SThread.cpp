#include <chrono>
#include <sstream>
#include "SThread.h"
#include "SRunnable.h"
void SThread::Sleep(long lMilliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(lMilliseconds));
}

unsigned int SThread::ThreadID()
{
    //将this_id转为uint
    std::stringstream ss;
    unsigned int id;
    std::thread::id this_id = std::this_thread::get_id();
    ss << this_id;
    ss >> id;
    return id;
}
SThread::SThread()
:m_bIsStart(false),m_bIsSuspend(false),m_pRunnable(this),m_lamEvent([](){})
{
    
}
SThread::SThread(SRunnable *pRunnable)
:m_bIsStart(false),m_bIsSuspend(false),m_pRunnable(pRunnable),m_lamEvent([](){})
{
    
}
SThread::SThread(std::function<void()> lamEvent)
:m_bIsStart(false),m_bIsSuspend(false),m_pRunnable(this),m_lamEvent(lamEvent)
{
    
}

SThread::~SThread(void)
{
    //XXX:如果是join或detach了主线程的,不应该回收资源
    if(!m_pThread->joinable())
        m_pThread.release();
}

bool SThread::Start(bool bSuspend)
{
    m_pThread = std::make_unique<std::thread>(&SThread::Enter,this);
    m_threadId = m_pThread->get_id();
    if(bSuspend)
        Suspend();
    
    m_bIsStart = m_pThread?true:false;
    return m_bIsStart;
}

void SThread::Run()
{
    m_lamEvent();
}

void SThread::Join(int timeout)
{
    m_pThread->join();
}

void SThread::Detach()
{
    m_pThread->detach();
}

void SThread::Resume()
{
    std::unique_lock<std::mutex> lock(m_cvM);
    lock.unlock();
    m_bIsSuspend = false;
    // 结束条件满足，唤醒所有等待该线程结束的线程
    m_cv.notify_all();
}

void SThread::Suspend()
{
    if (!m_bIsStart)
        return;
    
    std::unique_lock<std::mutex> lock(m_cvM);
    m_bIsSuspend = true;
    while(m_bIsSuspend)
    {
        m_cv.wait(lock);
    }
}

unsigned int SThread::GetThreadID()
{
    std::stringstream ss;
    unsigned int id;
    ss << m_threadId;
    ss >> id;
    return id;
}


void SThread::Enter()
{
    this->Run();
    
    m_bIsStart = false;
}
