/**
*
*    S2TransitionScene
*    @brief 场景过渡类
*    @author ZEROX
*    @link -
*    @version v1.0
*    @date 2017-09-25
*    @update 2017-09-25
*/

#ifndef _S2TRANSITIONSCENE_H_
#define _S2TRANSITIONSCENE_H_
#include "S2Scene.h"
class S2TransitionScene :public S2Scene
{
protected:
    S2TransitionScene(S2Scene *pScene);
    virtual ~S2TransitionScene();
public:
    //设置取得目标场景
    void SetTargetScene(S2Scene *pScene);
    const S2Scene *GetTargetScene();
private:
    S2Scene    *m_pScene;            //需要进行场景过渡的场景
};

#endif