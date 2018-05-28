#include "S2FrequencyClock.h"
#include <Windows.h>

S2FrequencyClock::S2FrequencyClock(bool bEnable)
:m_bEnable(bEnable)
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_dFreq); 
	Reset();
}
S2FrequencyClock::~S2FrequencyClock()
{

}

double S2FrequencyClock::GetClockTick()
{
	double lNow;
	double lFreq;
	QueryPerformanceFrequency((LARGE_INTEGER*)&lFreq);
	QueryPerformanceCounter((LARGE_INTEGER*)&lNow);
	return 1000.0*(lNow / lFreq);
}

double S2FrequencyClock::GetTick()
{
	double lNow;
	QueryPerformanceCounter((LARGE_INTEGER*)&lNow);
	return lNow;
}

double S2FrequencyClock::GetElpased()
{
	double lNow = GetTick();
	//如果加上m_dFixAll会造成与实际时间误差
	//如果频繁调用成员函数,会造成m_dFixAll积累,导致访问成员函数时间比实际所需延迟长
	//因此时钟不可以暂停

	return 1000.0*((double)(lNow - m_dLast - m_dFixAll)) / ((double)m_dFreq);	
	
}
void S2FrequencyClock::Pause()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&m_dFixStart);
}
void S2FrequencyClock::Resume()
{

	double lNow = GetTick();
	m_dFixAll += lNow - m_dFixStart;
}
void S2FrequencyClock::Reset()
{

	m_dFixAll = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&m_dLast);
}

void S2FrequencyClock::SetEnabled(bool bEnable){
	m_bEnable = bEnable;
	if (bEnable)Reset();
	else Pause();
}

bool S2FrequencyClock::GetEnabled(){
	return m_bEnable;
}
