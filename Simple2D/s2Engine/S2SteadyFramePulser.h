/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-14 14:52:40 
 * @Brief: 稳帧器
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-26 13:07:52
 * @Last Modified log: 
 */

#ifndef _S2STEADYFRAMEPULSER_H_
#define _S2STEADYFRAMEPULSER_H_
#include "../s2Base/sClock/SHighPrecClock.h"
#include "../s2Core/S2Object.h"
class S2SteadyFramePulser : public S2Object
{
public:
    S2SteadyFramePulser(double dDelay = 0.0165f);
    ~S2SteadyFramePulser();
public:
    //设置帧延迟,浮动率
    void SetFrameDelay(double dDelay, int nFreeRate = 10);
    double GetFrameDelay() const;

    void SetExtremeValue(double dLower, double dUpper);
    void GetExtremeValue(double &dLower, double &dUpper)const;

    void SetCurFrameDelay(double dDelay);
    double GetCurFrameDelay()const;

    bool Poll(bool bAdjust = true);
private:
    bool __Check();
    void __Adjust();
private:
    SHighPrecClock m_clock;         //高精度时钟
    double m_dExpectFrameDelay;     //期望帧率
    double m_dCurFrameDelay;        //实际帧率

    double m_dUpperLimit;           //上限值
    double m_dLowerLimit;           //下限值

    bool   m_bIsStart;              //是否开始调整
};

#endif