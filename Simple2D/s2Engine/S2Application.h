/**
*    S2Application
*    @brief 相关宏定义
*    @author cnscj
*    @link -
*    @version v1.0
*    @date 07/03/2018
*    @update 07/03/2018
*/

#ifndef _S2APPLICATION_H_
#define _S2APPLICATION_H_

#include "../s2Base/sDispatch/SDispatcher.h"
#include "../s2Base/sSchedule/SScheduler.h"
#include "../s2Core/S2Interface.hpp"

class S2Application : public S2Interface<S2Application>
{
public:
    //运行应用程序
    virtual void Run();

    //关闭应用程序
    virtual void Shutdowm();

    //应用程序主循环
    void MainLoop();
public:
    //取得全局定时器
    SScheduler *GetScheduler() const;
    //取得事件分发器
    SDispatcher *GetDispatcher() const;
public:
    /**
     * @brief 完成启动时调用
     * 
     * @return true 
     * @return false 
     */
    virtual bool ApplicationFinishLaunching() = 0;

    /**
     * @brief 进入后台调用
     * 
     */
    virtual void ApplicationEnterBackground() = 0;

    /**
     * @brief 从后台恢复到前台调用
     * 
     */
    virtual void ApplicationEnterForeground() = 0;
protected:
    S2Application();
    virtual ~S2Application();
private:
    SScheduler                    m_scheduler;                          //定时调度器
    SDispatcher                   m_dispatcher;                         //事件分发器
};
#endif