/**
*	S2FrequencyClock
*	@brief 高精度时钟
*	@author cnscj
*	@link -
*	@version v1.0
*	@date 07/03/2018
*	@update 07/03/2018
*/

#ifndef _S2CLOCK_H_
#define _S2CLOCK_H_

class S2FrequencyClock
{

public:
	S2FrequencyClock(bool bEnable = true);
	~S2FrequencyClock();
public:
	void SetEnabled(bool bEnable);	//设置状态
	bool GetEnabled();				//取得状态

	double 	GetTick();				//时间Tick
	double 	GetElpased();			//取得流逝的时间
	void 	Pause();				//暂停
	void 	Resume();				//继续
	void 	Reset();				//归零
public:
	//取得Tick
	static double GetClockTick();

protected:

	double	m_dFreq;                //时间精度
	double 	m_dLast;				//用于记录计时器启动时间
	double 	m_dFixStart;			//记录暂停开始时间
	double 	m_dFixAll;				//记录访问函数所花时间

	bool	m_bEnable;				//是否启用计时器
};

#endif