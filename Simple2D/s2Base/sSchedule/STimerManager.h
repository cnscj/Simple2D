/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-03-28 19:49:18 
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-17 11:38:30
 * @Brief: 任务调度器
 **/

#ifndef _STIMERMANAGER_H_
#define _STIMERMANAGER_H_
#include <unordered_set>
#include <queue>

class STimer;

class STimerManager
{
    typedef std::queue<STimer *> S2TimerPool;
public:
    //取得实例
    static STimerManager *GetInstance();
    static void DestroyInstance();
public:
    //添加定时器
    void AddTimer(STimer *pTimer);
    //移除定时器
    void RemoveTimer(STimer *pTimer);
    void RemoveTimersAll();

    //销毁定时器
    void DestroyTimer(STimer *pTimer);
    void DestroyTimersAll();

    //清理调度
    void Purge();

private:
    STimerManager();
    ~STimerManager();

    void SwapPool();
private:
    std::unordered_set<STimer *>       *m_setTimers;                   //定时器列表

    S2TimerPool                         *m_pCurReleasePool;             //当前要释放的池
    S2TimerPool                         *m_pCurBufferPool;              //当前缓存的池

    static STimerManager               *sm_pInstance;                  //全局唯一单例
};
#endif
