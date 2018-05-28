/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-05 19:12:51 
 * @Brief: 高精度定时器
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-17 11:18:43
 * @Last Modified log: 
 */

#ifndef _SHIGHPRECCLOCK_H_
#define _SHIGHPRECCLOCK_H_
#include <chrono>

class SHighPrecClock
{
    typedef std::chrono::steady_clock::time_point tp;
    typedef std::chrono::duration<double> dd;
    typedef std::chrono::high_resolution_clock hrc; //或者high_resolution_clock
  public:
    //取得Tick
    static double GetClockTick();

  public:
    SHighPrecClock();
    ~SHighPrecClock();

  public:
    double GetElpased(); //取得流逝的时间
    void Start();        //记录开始
    void Pause();        //暂停
    void Resume();       //继续
    void Stop();         //记录结束
    void Reset();        //重置

    //获取设置时间缩放率
    float GetTimeScale(void);
    void SetTimeScale(float fTimeScale);
  protected:
    tp m_begin;    //开始时间
    tp m_end;      //结束时间
    tp m_fixStart; //修正开始的时间
    dd m_fixTime;  //记录暂停所花时间

    float m_fTimeScale;//时间缩放尺度
};

#endif