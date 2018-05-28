/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-05 19:30:35
 * @Brief: 任务信息
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-17 11:37:03
 * @Last Modified log: 
 */

#ifndef _SSCHEDULE_STASK_H_
#define _SSCHEDULE_STASK_H_
#include<functional>

typedef struct tagTASK_INFO
{
    unsigned int            unId;             //任务ID
    double                  dInterval;        //时间间隔(ms)
    int                     nTimes;           //重复次数 - 每执行一次减一,最后一次后结束自己
    double                  dDelay;           //延迟时间(ms)
    double                  dNextTime;        //下一次执行时间
    std::function<void()>   lamEvent;         //所需要进行的操作

    //
    bool                    bEnabled;         //是否启用

    //
    double                  dUsedTime;        //上次执行所花的时间(默认值为1)
    unsigned int            unFlag;           //任务标记

}STask;

#endif
