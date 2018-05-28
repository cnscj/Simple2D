/**
*	SXFiniteTimeAction
*	@brief 有限次数动作类
*	@author ZEROX
*	@link -
*	@version v1.1
*	@date 10/03/2017
*	@update 10/03/2017
*/
#ifndef _S2FINITETIMEACTION_H_
#define _S2FINITETIMEACTION_H_
#include "S2Action.h"

class S2FiniteTimeAction : public S2Action
{
public:
	const static S2Result ACTION_RESULT_ONCE;   //执行一次
protected:
	S2FiniteTimeAction(S2Action	*pTarget=nullptr);
	virtual ~S2FiniteTimeAction();



public:
    //逻辑更新
    virtual S2Result Update(S2SceneNode *pNode,float fDelay);
    //取得目标
    virtual S2Action *GetTarget()const;
    //重置
    virtual void Reset();
	//一次执行回调
    S2Function<void(S2SceneNode *)> OnOnce;
private:
	S2Action	*m_pTarget;
};

#endif
