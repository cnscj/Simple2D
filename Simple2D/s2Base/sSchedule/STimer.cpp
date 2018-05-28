#include <chrono>
#include <sstream>
#include "STimer.h"
#include "STimerManager.h"

const double STimer::sm_dPrec = 1000000.f;//精度

STimer::STimer(std::function<void()> lamEvent , double dInterval , double dDelay , int nTimes)
:m_pThread(nullptr),m_bIsAutoRelease(false),m_bIsStart(false),m_bIsStop(false)
{
    m_taskInfo.unId = 0;
    m_taskInfo.lamEvent = lamEvent;
    m_taskInfo.dInterval = dInterval;
    m_taskInfo.dDelay = dDelay;
    m_taskInfo.nTimes = nTimes;
    m_taskInfo.bEnabled = true;
}
STimer::~STimer()
{
    if (m_bIsAutoRelease)
        return;
    Stop();

    //FIXME:自释放内存泄漏-如果Timer为临时变量会出问题
    m_pThread.release();
    m_pThread.reset(nullptr);
}
//开始定时器
void STimer::Start()
{
    if(!m_bIsStart)
    {
        m_bIsStart = true;
        m_bIsStop = false;
        std::chrono::steady_clock::time_point now;
        now = std::chrono::high_resolution_clock::now();
        m_pThread = std::make_unique<std::thread>(&STimer::Enter,this);
        std::thread::id thread_id = m_pThread->get_id();
        std::stringstream ss;
        ss << thread_id;
        ss >> m_taskInfo.unId;
        m_taskInfo.dNextTime = now.time_since_epoch().count() + m_taskInfo.dInterval * sm_dPrec;
        
        if(m_bIsAutoRelease)
            m_pThread->detach();
    }
    
}
//停止定时器-就是初始化
void STimer::Stop()
{
    if(m_bIsStart)
    {
        m_bIsStop = true;
        
        //while(!m_bIsStart);
        m_pThread->join();
        
        m_pThread.release();
        m_pThread.reset(nullptr);
        m_taskInfo.unId = 0;
    }
}


//是否自释放
STimer *STimer::AutoRelease()
{
    if(!m_pThread){
        m_bIsAutoRelease = true;
        return this;
    }
    
    if (!m_pThread->joinable())
    {
        m_bIsAutoRelease = true;
        m_pThread->detach();
    }
    return this;
}
bool STimer::IsAutoRelease()
{
    return m_bIsAutoRelease;
}

//设置事件
const std::function<void()> &  STimer::GetEvent()
{
    return m_taskInfo.lamEvent;
}
void STimer::SetEvent(std::function<void()> lamEvent)
{
    m_taskInfo.lamEvent = lamEvent;
}

//取得\设置时间间隔
double STimer::GetInterval() const
{
    return m_taskInfo.dInterval;
}
void STimer::SetInterval(double dInterval)
{
    m_taskInfo.dInterval = dInterval;
}

//取得\设置延迟时间
double STimer::GetDelay() const
{
    return m_taskInfo.dDelay;
}
void STimer::SetDelay(double dDelay)
{
    m_taskInfo.dDelay = dDelay;
}

//取得\设置重复次数
int STimer::GetTimes() const
{
    return m_taskInfo.nTimes;
}
void STimer::SetTimes(int nTime)
{
    m_taskInfo.nTimes = nTime;
}

//取得\设置启用状态
bool STimer::GetEnabled() const
{
    return m_taskInfo.bEnabled;
}

void STimer::SetEnalbed(bool bEnable)
{
    m_taskInfo.bEnabled = bEnable;
}

void STimer::Run()
{
    m_taskInfo.lamEvent();
}

void STimer::Enter()
{
    while (m_bIsStart)
    {
        if(m_bIsStop)
            break;
        
        if (m_taskInfo.bEnabled)
        {
            if (m_taskInfo.nTimes != 0)
            {
                std::chrono::steady_clock::time_point last;
                last = std::chrono::high_resolution_clock::now();
                double firsttime = (double)last.time_since_epoch().count();
                if( firsttime  >= m_taskInfo.dNextTime + m_taskInfo.dDelay * sm_dPrec)
                {
                    this->Run();
                    std::chrono::steady_clock::time_point now;
                    now = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> span = now-last;
                    double secondtime = (double)now.time_since_epoch().count();
                    m_taskInfo.dUsedTime = span.count()/sm_dPrec;
                    m_taskInfo.dNextTime = secondtime + m_taskInfo.dInterval * sm_dPrec;
                    --m_taskInfo.nTimes;
                }
            }else break;
        }
    }
    Exit();
}

void STimer::Exit()
{
    //结束
    m_bIsStart = false;
    
    //处与分离态时,子线程消亡连同数据一并删除
    if (!m_bIsStop && m_bIsAutoRelease)
    {
        //XXX:资源在主线程,当Timer为临时变量时可能会出错
        //delete this;
        STimerManager::GetInstance()->DestroyTimer(this);
    }
    
}
