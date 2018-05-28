#include <cmath>
#include "S2SteadyFramePulser.h"

S2SteadyFramePulser::S2SteadyFramePulser(double dDelay)
:m_bIsStart(false)
{
    SetFrameDelay(dDelay);
    m_dCurFrameDelay = m_dExpectFrameDelay;
    m_clock.Reset();
}
S2SteadyFramePulser::~S2SteadyFramePulser()
{

}

void S2SteadyFramePulser::SetFrameDelay(double dDelay, int nFreeRate)
{
    m_dUpperLimit = dDelay + ::fabs(dDelay * nFreeRate * 0.01f);
    m_dLowerLimit = dDelay + -::fabs(dDelay * nFreeRate * 0.01f);
    m_dExpectFrameDelay = GetFrameDelay();
}
double S2SteadyFramePulser::GetFrameDelay()const
{
    return (m_dUpperLimit + m_dLowerLimit) / 2.f;
}

void S2SteadyFramePulser::SetExtremeValue(double dLower, double dUpper)
{
    m_dLowerLimit = dLower;
    m_dUpperLimit = dUpper;
}
void S2SteadyFramePulser::GetExtremeValue(double &dLower, double &dUpper)const
{
    dLower = m_dLowerLimit;
    dUpper = m_dUpperLimit;
}

void S2SteadyFramePulser::SetCurFrameDelay(double dDelay)
{
    m_dExpectFrameDelay = dDelay;
}

double S2SteadyFramePulser::GetCurFrameDelay()const
{
    return m_dCurFrameDelay;
}

bool S2SteadyFramePulser::Poll(bool bAdjust)
{
    double dElpased = m_clock.GetElpased();
    if (dElpased >= m_dExpectFrameDelay)
    {
        m_dCurFrameDelay = dElpased;
        m_clock.Reset();

        if (bAdjust)
        {
            if (__Check())
            {
                __Adjust();
            }    
        }

        return true;
    }
    return false;
}

bool S2SteadyFramePulser::__Check()
{
    if (m_dCurFrameDelay > m_dUpperLimit || m_dCurFrameDelay < m_dLowerLimit)
    {
        m_bIsStart = true;
    }
    return m_bIsStart;
}

void S2SteadyFramePulser::__Adjust()
{
    //如果再次修正已经无法达到预设值,将会一直修正,证明游戏逻辑有问题
    double dSettingFrameDelay = GetFrameDelay();
    if (m_dCurFrameDelay > dSettingFrameDelay)
    {
        if (m_dCurFrameDelay - dSettingFrameDelay < 0.0001f)
            m_bIsStart = false;
        else m_dExpectFrameDelay -= 0.0001f;

    }
    else if (m_dCurFrameDelay < dSettingFrameDelay)
    {
        if (m_dCurFrameDelay - dSettingFrameDelay > -0.0001f)
            m_bIsStart = false;
        else m_dExpectFrameDelay += 0.0001f;

    } 
}
