#include "SHighPrecClock.h"

double SHighPrecClock::GetClockTick()
{
    tp now = hrc::now();
    return (double)now.time_since_epoch().count();
}
SHighPrecClock::SHighPrecClock()
:m_fTimeScale(1.0f)
{
    Reset();
}
SHighPrecClock::~SHighPrecClock()
{
}

double SHighPrecClock::GetElpased()
{
    tp time;
    dd span;
    if (m_begin >= m_end)
    {
        time = hrc::now();
    }
    else
    {
        time = m_end;
    }

    span = time - m_begin - m_fixTime;
    return span.count() * m_fTimeScale;
}
void SHighPrecClock::Start()
{
    m_begin = hrc::now();
}

void SHighPrecClock::Stop()
{
    m_end = hrc::now();
}
void SHighPrecClock::Reset()
{
    m_end = m_begin = hrc::now();
    m_fixTime = dd(0);
}

void SHighPrecClock::Pause()
{
    m_fixStart = hrc::now();
}

void SHighPrecClock::Resume()
{
    tp end = hrc::now();
    m_fixTime += std::chrono::duration_cast<dd>(end - m_fixStart);
}

//获取设置时间缩放率
float SHighPrecClock::GetTimeScale(void)
{
    return m_fTimeScale;
}
void SHighPrecClock::SetTimeScale(float fTimeScale)
{
    m_fTimeScale = fTimeScale;
}