/**
*	SXActionInstant
*	@brief 瞬时完成动作类
*	@author ZEROX
*	@link -
*	@version v1.1
*	@date 10/03/2017
*	@update 10/03/2017
*/
#ifndef _S2ACTIONINSTANT_H_
#define _S2ACTIONINSTANT_H_
#include "S2FiniteTimeAction.h"
class S2ActionInstant :public S2FiniteTimeAction
{
public:
	S2ActionInstant(S2Action *pTarget);
	virtual ~S2ActionInstant();

};
#endif