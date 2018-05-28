/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-08 09:12:40 
 * @Brief: 线程类
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-17 11:40:02
 * @Last Modified log: 
 */

#ifndef _STHREAD_H_
#define _STHREAD_H_
#include <string>
#include <thread>
#include <condition_variable>
#include <memory>
#include <functional>
#include "SRunnable.h"
class SThread : public SRunnable
{
public:
    /**
     * @brief 线程休眠
     * 
     * @param lMilliseconds 休眠多少毫秒
     */
    static void Sleep(long lMilliseconds);

    /**
     * @brief 返回线程ID
     * 
     * @return unsigned int 线程ID
     */
    static unsigned int ThreadID();

public:
    SThread();
    SThread(SRunnable *pRunnable);
    SThread(std::function<void()> lamEvent);
    ~SThread(void);

    /**
     * @brief 开始运行线程
     * 
     * @param bSuspend 开始运行时是否挂起
     * @return true 
     * @return false 
     */
    bool Start(bool bSuspend = false);

    /**
     * @brief 运行的线程函数，可以使用派生类重写此函数
     * 
     */
    virtual void Run();

    /**
     * @brief 当前执行此函数线程等待线程结束
     * 
     * @param timeout 等待超时时间，如果为负数，等待无限时长
     */
    void Join(int timeout = -1);

    /**
     * @brief 与主线程分离,成为孤儿线程,主线程退出不影响子线程
     * 
     */
    void Detach();

    /**
     * @brief 恢复挂起的线程
     * 
     */
    void Resume();

    /**
     * @brief 挂起线程
     * 
     */
    void Suspend();

    /**
     * @brief 取得线程ID
     * 
     * @return unsigned int 返回线程ID
     */
    unsigned int GetThreadID();

private:
    /**
     * @brief 线程入口
     * 
     */
    void Enter();
private:
    std::unique_ptr<std::thread> m_pThread;              //线程类 
    std::thread::id              m_threadId;             //线程ID
    std::mutex                   m_cvM;                  //同步信号量
    std::condition_variable      m_cv;                   //同步条件
    volatile bool                m_bIsSuspend;           //线程是否被挂起
    volatile bool                m_bIsStart;             //线程是否已经开始运行


    SRunnable const             *m_pRunnable;           //线程接口
    std::function<void()>        m_lamEvent;             //lam表达式
};

#endif  