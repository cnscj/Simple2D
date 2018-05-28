#include "../s2Base/sMemory/SAutoReleasePoolManager.h"
#include "../s2Base/sSchedule/STimerManager.h"
#include "../s2Scene/S2Director.h"
#include "S2Application.h"
S2Application::S2Application()
:S2Interface(nullptr)
{
    S2Interface::SetInstance(this);
}
S2Application::~S2Application()
{
    Shutdowm();
}

//运行应用程序
void S2Application::Run()
{
    ApplicationFinishLaunching();
       
}

//关闭应用程序
void S2Application::Shutdowm()
{
    S2Director::DestroyInstance();

    SAutoReleasePoolManager::DestroyInstance();
    STimerManager::DestroyInstance();

}

//应用程序主循环
void S2Application::MainLoop()
{
    GetDispatcher()->DealAllEvents();
    GetScheduler()->DealAllTasks();

    S2Director::GetInstance()->MainLoop();

    SAutoReleasePoolManager::GetInstance()->Purge();
    STimerManager::GetInstance()->Purge();
}

//取得全局定时器
SScheduler *S2Application::GetScheduler() const
{
    return (SScheduler *)&m_scheduler;
}
//取得事件分发器
SDispatcher *S2Application::GetDispatcher() const
{
    return (SDispatcher *)&m_dispatcher;
}