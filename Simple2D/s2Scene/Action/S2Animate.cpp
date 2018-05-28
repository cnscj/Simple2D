/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-18 11:04:26 
 * @Brief: 动画播放类实现
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-27 15:30:24
 * @Last Modified log: 
 */

#include "S2Animate.h"
#include "../S2SpriteAnimation.h"
#include "../S2Sprite.h"

S2Animate::S2Animate(S2SpriteAnimation *pSpriteAnimation)
:S2ActionInterval(nullptr)
{
    SetSpriteAnimation(pSpriteAnimation);
}
S2Animate::~S2Animate()
{
    S2SAFERELEASE(m_pSpriteAnimation);
}
//设置\获取精灵动画
void S2Animate::SetSpriteAnimation(S2SpriteAnimation *pSpriteAnimation)
{
    if (pSpriteAnimation)
    {
        S2SAFERELEASE(m_pSpriteAnimation);
        //权限转移
        SetInterval(0);

        m_pSpriteAnimation = pSpriteAnimation;
        m_pSpriteAnimation->Retain();
    }
}
S2SpriteAnimation *S2Animate::GetSpriteAnimation() const
{
    return m_pSpriteAnimation;
}

//逻辑更新
S2Result S2Animate::OnUpdate(S2SceneNode *pNode,float fDelay)
{
    //对返回情况做判断
    S2Sprite *pSprite = static_cast<S2Sprite *>(pNode);
    S2Result res = m_pSpriteAnimation->Update(pSprite,fDelay);
    return (res == 0?ACTION_RESULT_NORMAL:(res == 1?ACTION_RESULT_FRAME:(res == 2?ACTION_RESULT_ONCE:ACTION_RESULT_FINISH)));
}