/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-27 12:06:40 
 * @Brief: 延时动作定义
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-27 16:01:35
 * @Last Modified log: 
 */
#include "S2ActionInterval.h"
const S2Result S2ActionInterval::ACTION_RESULT_FRAME = GetResultUID();   //执行一帧

S2ActionInterval::S2ActionInterval(S2Action *pTarget,double dInterval,double dDelay,int nTimes)
:S2FiniteTimeAction(pTarget), m_dInterval(dInterval), m_dNextTime(0), m_dTotalTime(0), m_dDelay(dDelay), m_nTimes(nTimes), OnFrame([](S2SceneNode *){})
{

}
S2ActionInterval::~S2ActionInterval()
{

}

void S2ActionInterval::SetInterval(double dInterval)
{
    m_dInterval = dInterval;
}
double S2ActionInterval::GetInterval()const
{
    return m_dInterval;
}

void S2ActionInterval::SetDelay(double dDelay)
{
    m_dDelay = dDelay;
}
double S2ActionInterval::GetDelay()const
{
    return m_dDelay;
}

void S2ActionInterval::SetTimes(int nTimes)
{
    m_nTimes = nTimes;
}
int S2ActionInterval::GetTimes()const
{
    return m_nTimes;
}
//逻辑更新
S2Result S2ActionInterval::Update(S2SceneNode *pNode,float fDelay)
{
    m_dTotalTime+=fDelay;
    
    if (m_nTimes != 0)
    {    
        if( m_dTotalTime >= m_dNextTime+m_dDelay)
        {
            S2Result res = S2FiniteTimeAction::Update(pNode,fDelay);
            if(res == ACTION_RESULT_FRAME)
            {
                OnFrame(pNode);
            }

            m_dNextTime = m_dNextTime + m_dInterval;
            --m_nTimes;
        
            if(m_nTimes == 0) return ACTION_RESULT_FINISH;
            return res;
        }
    }
    return ACTION_RESULT_NORMAL;
}
