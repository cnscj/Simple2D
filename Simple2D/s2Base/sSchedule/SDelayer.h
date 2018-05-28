/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-05 19:30:35 
 * @Brief: 延时器
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-17 11:36:12
 * @Last Modified log: 
 */

#ifndef _SDELAYER_H_
#define _SDELAYER_H_
#include "STimer.h"

class SDelayer : public STimer
{
public:
    SDelayer(std::function<void()> lamEvent = [=](){},double dDelay = 1000);
    virtual ~SDelayer();
private:
    /* 屏蔽函数 */
    using STimer::GetInterval;
    using STimer::SetInterval;
    using STimer::GetTimes;
    using STimer::SetTimes;

};

#endif