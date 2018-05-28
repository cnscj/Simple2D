/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-27 10:44:54 
 * @Brief: 重复动作类
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-27 15:44:18
 * @Last Modified log: 
 */
#ifndef _S2ACTIONREPEAT_H_
#define _S2ACTIONREPEAT_H_
#include "S2FiniteTimeAction.h"
class S2ActionRepeat :public S2FiniteTimeAction
{
public:
	S2ActionRepeat(S2Action *pTarget,int nTimes=1);
	virtual ~S2ActionRepeat();
public:
    virtual void SetTimes(int nTimes);
    virtual int GetTimes() const;
protected:
	//逻辑更新
	virtual S2Result Update(S2SceneNode *pNode,float fDelay);

private:
	int 			m_nTimes;		//重复次数
};
#endif