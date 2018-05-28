/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-03-28 19:49:18
 * @Brief: 任务调度器
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-17 11:36:48
 * @Last Modified log: 
 */

#ifndef _SSCHEDULER_H_
#define _SSCHEDULER_H_
#include <set>
#include <queue>
#include "STask.h"
class SScheduler
{
    //任务自定义排序函数-调度策略
    struct TaskCmp
    {
        bool operator()(const STask* k1, const STask* k2)
        {
            return 1 / CalculateWeight(k1) < 1 / CalculateWeight(k2);
        }
        
        double CalculateWeight(const STask* k)
        {
            //优先级 = (作业已等待时间 + 作业的服务时间) / 作业的服务时间
            return (k->dInterval + k->dUsedTime)/k->dUsedTime;
        }
    };
    typedef std::set<STask*,TaskCmp>                                 TaskSet;

    typedef std::queue<std::pair<int, TaskSet::iterator> >            TaskIteratorQueue;
    typedef std::pair<int, TaskSet::iterator>                         TaskIteratorPair;
public:
    SScheduler();
    ~SScheduler();
public:
    //获取设置时间缩放率
    float GetTimeScale(void);
    void SetTimeScale(float fTimeScale);
public:
    /**
     * @brief 设置任务-按照时间间隔顺序进行插入
     *
     * @param func 回调函数
     * @param interval 时间间隔
     * @param delay 延迟时间
     * @param repeat 重复次数
     * @return S2uInt 返回任务id
     */
    unsigned int AddTask(std::function<void()> func, double interval=1, double delay=0, int repeat=-1);
    
    /**
     * @brief 撤销调度
     *
     * @S2uInt id 任务id
     */
    void RemoveTask(unsigned int id, bool bRelease = false);
    
    /**
     * @brief 撤销所有任务
     *
     */
    void RemoveAllTasks(bool bRelease = false);
    
    /**
     * @brief 任务是否暂停
     *
     * @param id 任务ID
     * @return true
     * @return false
     */
    bool IsTaskPaused(unsigned int id);
    
    /**
     * @brief 暂停任务
     *
     * @param id 任务id
     */
    void PauseTask(unsigned int id);
    
    /**
     * @brief 恢复任务
     *
     * @param id 任务id
     */
    void ResumeTask(unsigned int id);
    
public:
    //开始调度
    void ScheduleAllTasks(float fDt);

    //处理所有任务
    void DealAllTasks(float fTimeScale = 1.0f);
private:
    //调度前
    void __OnPreSchedule(float fDt);
    //调度时
    void __OnScheduling(float fDt);
    void __OnScheduling();
    //调度后
    void __OnAftSchedule(float fDt);
    
private:
    
    //取得任务
    STask *__GetTask(unsigned int id);
    
    //取得任务
    TaskSet::iterator __GetTaskIterator(unsigned int id);
    
    //销毁任务
    void __DestroyTask(unsigned int id);
    
    //任务检查
    bool __CheckTask(TaskSet::iterator &it);
    
    //取得事件戳
    double __GetTimeTick();
private:
    unsigned int                                      m_unTaskIds;          //记录下一个TaskId
    TaskSet                                           m_setTasks;           //任务列表
    std::queue<STask *>                              m_queAddTasks;        //要加入的任务
    TaskIteratorQueue                                 m_queDirtyTasks;      //变更的任务
    
    double                                            m_dTimePoint;         //记录时间点
    float                                             m_fTimeScale;         //时间缩放率
};
#endif

