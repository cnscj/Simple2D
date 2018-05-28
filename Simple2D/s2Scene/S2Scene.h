/**
*    S2Scene
*    @brief 场景类
*    @author cnscj
*    @link -
*    @version v1.0
*    @date 07/03/2018
*    @update 07/03/2018
*/

#ifndef _S2SCENE_H_
#define _S2SCENE_H_
#include "S2SceneNode.h"

class S2Scene :public S2SceneNode
{
public:
    S2Scene();
    virtual ~S2Scene();
public:
    //进入结点
    void Enter();
    //退出结点
    void Exit();
    //暂停
    void Pause();
    //恢复
    void Resume();
protected:
    /* 生命周期接口 */
    //进入场景
    virtual void OnEnter();                       //进入场景时候触发。
    //进入场景的特效
    virtual void OnEnterTransitionDidFinish();    //进入场景而且过渡动画结束时候触发。
    //退出场景
    virtual void OnExit();                        //退出场景时候触发。
    //退出场景的特效
    virtual void OnExitTransitionDidStart();      //退出场景而且开始过渡动画时候触发。
    /////
    //场景暂停调用
    virtual void OnPause();
    //场景恢复调用
    virtual void OnResume();
private:
    ////
    bool                    m_bIsPause;            //场景是否被暂停

};
#endif