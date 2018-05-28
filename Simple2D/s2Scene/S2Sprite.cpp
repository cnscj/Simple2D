/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-07 16:48:14 
 * @Brief: 精灵实现
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-07 17:59:18
 * @Last Modified log: 
 */
#include "S2Sprite.h"
#include "S2SpriteFrame.h"
#include "S2SpriteAnimation.h"
#include "Action/S2Animate.h"
#include "../s2Render/S2Renderer.h"
#include "../s2Render/S2Graphics.h"
#include "../s2Render/S2Texture.h"
#include "../s2Base/sMath/SMathX.hpp"
S2Sprite::S2Sprite()
:m_pMainFrame(nullptr),  m_pAnimate(nullptr)
, m_dwColorKey(0xffffffff), m_fOpacity(1.f)
, m_fRadian(0.f)
, m_vec3Rotation3D(0.f,0.f,0.f)
, m_fSkewX(0), m_fSkewY(0)
, m_fScaleX(1.f), m_fScaleY(1.f)
, m_bFlipX(false), m_bFlipY(false)
{
    
}
S2Sprite::~S2Sprite()
{
    S2SAFERELEASE(m_pMainFrame);
    S2SAFERELEASE(m_pAnimate);
}

//通过精灵帧创建精灵-尺寸使用精灵帧的尺寸
S2Sprite *S2Sprite::CreateWithSpriteFrame(S2SpriteFrame *pSpriteFrame)
{
    pSpriteFrame->Retain();
    m_pMainFrame = pSpriteFrame;
    SetSize(m_pMainFrame->GetFrameWidth(), m_pMainFrame->GetFrameHeight());
    return this;
}
//通过纹理创建精灵
S2Sprite *S2Sprite::CreateWithTexture(S2Texture *pTexture, const S2Rect *rt)
{
    auto pSpriteFrame = S2Object::Create<S2SpriteFrame>(pTexture, rt);
    if (pSpriteFrame){
        SetSpriteFrame(pSpriteFrame);
        SetSize(m_pMainFrame->GetFrameWidth(), m_pMainFrame->GetFrameHeight());
        return this;
    }
    return nullptr;
}
//从文件中加载
S2Sprite *S2Sprite::CreateWithFile(const S2String &strPath, const S2Rect *rt)
{
    auto pSpriteFrame = S2Object::Create<S2SpriteFrame>(strPath, rt);
    if (pSpriteFrame){
        SetSpriteFrame(pSpriteFrame);
        SetSize(m_pMainFrame->GetFrameWidth(), m_pMainFrame->GetFrameHeight());
        return this;
    }
    return nullptr;
}
//从资源中加载
S2Sprite *S2Sprite::CreateWithResource(S2uInt uRcid,const S2Rect *rt)
{
    auto pSpriteFrame = S2Object::Create<S2SpriteFrame>(uRcid, rt);
    if (pSpriteFrame){
        SetSpriteFrame(pSpriteFrame);
        SetSize(m_pMainFrame->GetFrameWidth(), m_pMainFrame->GetFrameHeight());
        return this;
    }
    return nullptr;
}
//从内存中创建
S2Sprite *S2Sprite::CreateWithMemory(const S2Data in, S2uInt length, const S2Rect *rt)
{
    auto pSpriteFrame = S2Object::Create<S2SpriteFrame>(in, length, rt);
    if (pSpriteFrame){
        SetSpriteFrame(pSpriteFrame);
        SetSize(m_pMainFrame->GetFrameWidth(), m_pMainFrame->GetFrameHeight());
        return this;
    }
    return nullptr;
}
//从动画中创建
S2Sprite *S2Sprite::CreateWithAnimation(S2SpriteAnimation *pAnimation)
{
    if (PlayAnimation(pAnimation))
    {
        AdaptiveSize();
        return this;
    }
    return nullptr;
}
//从动画的某帧创建
S2Sprite *S2Sprite::CreateWithAnimationIndex(const S2SpriteAnimation *pAnimation, S2uInt index)
{
    if (pAnimation)
    {
        auto pSpriteFrame = pAnimation->GetFrameByIndex(index);
        if (pSpriteFrame)
        { 
            SetSpriteFrame(pSpriteFrame);
            SetSize(m_pMainFrame->GetFrameWidth(), m_pMainFrame->GetFrameHeight());
            return this;
        }

    }
    return nullptr;
}
///

//更换新的精灵帧
void S2Sprite::SetSpriteFrame(S2SpriteFrame *pFrame)
{
    S2SAFERELEASE(m_pMainFrame);
    m_pMainFrame = pFrame;
    m_pMainFrame->Retain();
}
const S2SpriteFrame *S2Sprite::GetSpriteFrame() const
{
    return m_pMainFrame;
}


//设置色键
void S2Sprite::SetColorKey(S2ColorRef dwColorKey)
{
    m_dwColorKey = dwColorKey;
}
const S2ColorRef &S2Sprite::GetColorKey()
{
    return m_dwColorKey;
}

//设置不透明度
void S2Sprite::SetOpacity(float fOpacity)
{
    m_fOpacity = fOpacity;
}

float S2Sprite::GetOpacity() const
{
    return m_fOpacity;
}

//自适应纹理大小
void S2Sprite::AdaptiveSize()
{
    if (GetSpriteFrame())
    {
        SetSize(GetSpriteFrame()->GetFrameWidth(), GetSpriteFrame()->GetFrameHeight());
    }
}

//设置旋转
void S2Sprite::SetRotation(float fRadian)
{
    m_fRadian = fRadian;
    ChangeFlag(MATRIX_CHANGED, true);
}
void S2Sprite::SetRotation3D(float x, float y, float z)
{
    m_vec3Rotation3D.x = x;
    m_vec3Rotation3D.y = y;
    m_vec3Rotation3D.z = z;
    ChangeFlag(MATRIX_CHANGED, true);
}

//水平竖直翻转
void S2Sprite::SetFlipX(bool bFlip)
{
    m_bFlipX = bFlip;
    ChangeFlag(MATRIX_CHANGED, true);
}
void S2Sprite::SetFlipY(bool bFlip)
{
    m_bFlipY = bFlip;
    ChangeFlag(MATRIX_CHANGED, true);
}

//关于XY轴倾斜
void S2Sprite::SetSkewX(float fSkewX)
{
    m_fSkewX = fSkewX;
    ChangeFlag(MATRIX_CHANGED, true);
}
void S2Sprite::SetSkewY(float fSkewY)
{
    m_fSkewY = fSkewY;
    ChangeFlag(MATRIX_CHANGED, true);
}

//设置缩放比率
void S2Sprite::SetScale(float fScale)
{
    SetScaleX(fScale);
    SetScaleY(fScale);
}
void S2Sprite::SetScaleX(float fScaleX)
{
    m_fScaleX = fScaleX;
    ChangeFlag(MATRIX_CHANGED, true);
}
void S2Sprite::SetScaleY(float fScaleY)
{
    m_fScaleY = fScaleY;
    ChangeFlag(MATRIX_CHANGED, true);
}

//当成一种永远重复的动作来处理
S2Animate *S2Sprite::PlayAnimation(S2SpriteAnimation *pAnimation)
{
    StopAnimation();
    if (pAnimation)
    {
        //动画动作应为一个单例
        auto pAnimate = S2Object::Create<S2Animate>(pAnimation);
        
        if (pAnimate)
        {
            m_pAnimate = pAnimate;
            m_pAnimate->Retain();

                auto pSpriteFrame = pAnimation->GetCurFrame();
                if (pSpriteFrame)
                {
                    SetSpriteFrame(pSpriteFrame);
                }
            RunAction(pAnimate);
        }
        return pAnimate;
    }

    return nullptr;
}
void S2Sprite::StopAnimation()
{
    StopAction(m_pAnimate);
    S2SAFERELEASE(m_pMainFrame);
    S2SAFERELEASE(m_pAnimate);
}

///
//重载逻辑更新函数
void S2Sprite::OnUpdate(float fDelay)
{

    

}
//绘制结点
void S2Sprite::OnDraw(S2Renderer *pRenderer, const S2Matrix *mat4, S2uInt flag)
{
    if (m_pMainFrame)
    {
        //图形渲染器
        auto pGraphics = pRenderer->CreateGraphics();
        auto descPos = ConvertToAbsLeftTopPos();
        auto descRect = &GetRectWithPos(descPos);
        auto srcRect = &GetSpriteFrame()->GetFrameRect();
        auto fOpacity = GetOpacity();
        auto dwColorKey = GetColorKey();
        auto pWorldMatrix = GetWorldMatrix();

        //关键色
        S2ColorRef dwAlphaColor = (S2ColorRef)(dwColorKey & 0x00ffffff) | ((S2ColorRef)(fOpacity * (dwColorKey >> 24 & 0xff)) << 24);

        //脏标记发,只有当矩阵发生改变时重新计算值
        if (GetFlag() & MATRIX_CHANGED)
        {
            //TODO:应该用脏标记法,
            //TODO:缺少绕轴,倾斜,翻转的变幻
            auto descAbsPos = ConvertToAbsPos();
            auto descAbsRect = &GetRectWithPos(descAbsPos);
            S2Matrix worldMatrix;

            //应该围绕中心点旋转
            SMatrixTransformation2D(
                &worldMatrix,
                &S2Vector2((float)descAbsRect->GetX(), (float)descAbsRect->GetY()),
                0.f,
                &S2Vector2(m_fScaleX, m_fScaleY),
                &S2Vector2((float)descAbsRect->GetX(), (float)descAbsRect->GetY()),
                m_fRadian,
                (S2Vector2*)nullptr
                );

            SetWorldMatrix(&worldMatrix);

            ChangeFlag(MATRIX_CHANGED, false);
        }

        //渲染
        pGraphics->DrawTexture(
            m_pMainFrame->GetTexture(),
            descRect,
            srcRect,
            pWorldMatrix,
            dwAlphaColor,
            0
        );
    
    }
}

