/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-18 09:20:32 
 * @Brief: 动画行为
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-27 11:26:25
 * @Last Modified log: 
 */

#ifndef _S2ANIMATE_H_
#define _S2ANIMATE_H_
#include "S2ActionInterval.h"
class S2SpriteAnimation;
class S2Animate : public S2ActionInterval
{
    friend class S2Sprite;
public:
    //TODO:这种创建方式不严谨,无法得知是否创建成功
    S2Animate(S2SpriteAnimation *pSpriteAnimation);
    ~S2Animate();
public:
    //设置\获取精灵动画
    void SetSpriteAnimation(S2SpriteAnimation *pSpriteAnimation);
    S2SpriteAnimation *GetSpriteAnimation() const;
protected:
    //逻辑更新
    virtual S2Result OnUpdate(S2SceneNode *pNode,float fDelay);
private:
    //精灵动画
    S2SpriteAnimation   *m_pSpriteAnimation;        //动画精灵
};

#endif