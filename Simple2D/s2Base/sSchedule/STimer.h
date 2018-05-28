/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-05 19:30:35
 * @Brief: 定时器-异步
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-17 11:37:47
 * @Last Modified log: 
 */

#ifndef _STIMER_H_
#define _STIMER_H_
#include <thread>
#include <functional>
#include <memory>
#include "STask.h"

class STimer
{
    friend class STimerManager;
public:
    STimer(std::function<void()> lamEvent = [](){}, double dInterval = 1000, double dDelay = 0, int nTimes = -1);
    STimer(const STimer &) = delete;
    virtual ~STimer();
public:
    //开始定时器
    void Start();
    //停止定时器
    void Stop();

    //是否自释放
    STimer *AutoRelease();
    bool IsAutoRelease();

    //设置事件
    const std::function<void()> &GetEvent();
    void SetEvent(std::function<void()> lamEvent);

    //取得\设置时间间隔(单位s)
    double GetInterval() const;
    void SetInterval(double dInterval);

    //取得\设置延迟时间
    double GetDelay() const;
    void SetDelay(double dDelay);

    //取得\设置重复次数
    int GetTimes() const;
    void SetTimes(int nTime);

    //取得\设置启用状态
    bool GetEnabled() const;
    void SetEnalbed(bool bEnable);

public:
    //运行逻辑
    virtual void Run();
private:
    //线程入口
    void Enter();

    void Exit();

private:
    std::unique_ptr<std::thread>      m_pThread;         //线程

    bool             m_bIsStart;         //是否已经开始
    bool             m_bIsStop;          //是否停止
    bool             m_bIsAutoRelease;   //是否自释放
    STask           m_taskInfo;          //任务信息

    const static double sm_dPrec;        //精度
};
#endif
