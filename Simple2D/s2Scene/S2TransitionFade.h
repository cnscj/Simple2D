
/**
*
*    S2TransitionFade
*    @brief 场景过渡-渐渐褪去
*    @author ZEROX
*    @link -
*    @version v1.0
*    @date 2017-09-25
*    @update 2017-09-25
*/

#ifndef _S2TRANSITIONFADE_H_
#define _S2TRANSITIONFADE_H_
#include "S2TransitionScene.h"
//变暗消失后，另一场景慢慢出现
class S2TransitionFade :public S2TransitionScene
{
protected:
    //进入场景
    virtual void OnEnter();                       //进入场景时候触发。
    //进入场景的特效
    virtual void OnEnterTransitionDidFinish();    //进入场景而且过渡动画结束时候触发。
    //退出场景
    virtual void OnExit();                        //退出场景时候触发。
    //退出场景的特效
    virtual void OnExitTransitionDidStart();      //退出场景而且开始过渡动画时候触发。
};

#endif