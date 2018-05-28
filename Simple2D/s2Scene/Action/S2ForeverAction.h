/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-24 09:24:00 
 * @Brief: 无限次动作
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-27 13:43:04
 * @Last Modified log: 
 */

#ifndef _S2FOREVERACTION_H_
#define _S2FOREVERACTION_H_
#include "S2Action.h"

class S2ForeverAction : public S2Action
{
public:
	const static S2Result ACTION_RESULT_ONCE;  //执行一次
protected:
    S2ForeverAction(S2Action *pTarget);
    virtual ~S2ForeverAction();

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