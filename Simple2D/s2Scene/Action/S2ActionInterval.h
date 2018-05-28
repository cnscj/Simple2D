/**
*	SXActionInstant
*	@brief 间隔完成动作类
*	@author ZEROX
*	@link -
*	@version v1.1
*	@date 10/03/2017
*	@update 10/03/2017
*/
#ifndef _S2ACTIONINTERVAL_H_
#define _S2ACTIONINTERVAL_H_
#include "S2FiniteTimeAction.h"
class S2ActionInterval :public S2FiniteTimeAction
{
public:
	const static S2Result ACTION_RESULT_FRAME;  //执行一帧
public:
	S2ActionInterval(S2Action *pTarget,double dInterval = 0.1f,double dDelay = 0,int nTimes=-1);
	virtual ~S2ActionInterval();
public:
    virtual void SetInterval(double dInterval);
    virtual double GetInterval()const;

    virtual void SetDelay(double dDelay);
    virtual double GetDelay()const;

    virtual void SetTimes(int nTimes);
    virtual int GetTimes()const;
	//一帧的回调
    S2Function<void(S2SceneNode *)> OnFrame;
public:
	//逻辑更新
    virtual S2Result Update(S2SceneNode *pNode,float fDelay);
private:
	double		m_dInterval;		//时间间隔
	double 		m_dNextTime;		//下次执行时间
	double		m_dTotalTime;		//时间记录

	double		m_dDelay;			//延迟时间

	int			m_nTimes;			//次数
};
#endif