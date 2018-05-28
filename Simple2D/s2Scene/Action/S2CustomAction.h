/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-24 19:17:30 
 * @Brief: 自定义行为
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-27 15:53:51
 * @Last Modified log: 
 */

#ifndef _S2CUSTOMACTION_H_
#define _S2CUSTOMACTION_H_
#include "S2Action.h"

class S2CustomAction : public S2Action
{
public:
    S2CustomAction(S2Function<S2Result(S2SceneNode *pNode, float fDelay)> OnHandler = [=](S2SceneNode *pNode, float fDelay)
    {
        return S2Action::ACTION_RESULT_FINISH;
    });
    ~S2CustomAction();
public:
    //逻辑更新
    S2Function<S2Result(S2SceneNode *pNode,float fDelay)> OnHandler;
protected:
    virtual S2Result OnUpdate(S2SceneNode *pNode,float fDelay) {return OnHandler(pNode,fDelay);}
};
#endif