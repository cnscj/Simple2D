/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-18 12:11:47 
 * @Brief: 精灵帧
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-18 21:13:15
 * @Last Modified log: 
 */
#include "S2SpriteFrame.h"
#include "S2Director.h"
#include "../s2Render/S2Texture.h"
S2SpriteFrame::S2SpriteFrame()
:m_pTexture(nullptr), m_frameRect(0,0,0,0)
{

}
S2SpriteFrame::S2SpriteFrame(S2Texture *pTexture, const S2Rect *rt)
{
    CreateWithTexture(pTexture,rt);
}
S2SpriteFrame::S2SpriteFrame(S2String strPath, const S2Rect *rt)
{
    CreateWithFile(strPath, rt);
}
S2SpriteFrame::S2SpriteFrame(S2uInt uRcid, const S2Rect *rt)
{
    CreateWithResource(uRcid, rt);
}
S2SpriteFrame::S2SpriteFrame(const S2Data data, const S2uInt length, const S2Rect *rt)
{
    CreateWithMemory(data,length, rt);
}

S2SpriteFrame::~S2SpriteFrame()
{
    __ReleaseTexture();
}

//通过纹理创建精灵帧
S2SpriteFrame *S2SpriteFrame::CreateWithTexture(S2Texture *pTexture, const S2Rect *rt)
{
    __ReleaseTexture();
    m_pTexture = pTexture;
    m_pTexture->Retain();
    SetFrameRect(rt);
    return pTexture?this:nullptr;
}
//从文件中加载
S2SpriteFrame *S2SpriteFrame::CreateWithFile(S2String strPath, const S2Rect *rt)
{
    __ReleaseTexture();
    auto pTexture = S2Director::GetInstance()->GetRenderView()->GetViewRenderer()->CreateTextureWithFile(strPath);
    m_pTexture = pTexture;
    m_pTexture->Retain();
    SetFrameRect(rt);
    return pTexture?this:nullptr;
}
//从资源中加载
S2SpriteFrame *S2SpriteFrame::CreateWithResource(S2uInt uRcid, const S2Rect *rt)
{
    __ReleaseTexture();
    auto pTexture = S2Director::GetInstance()->GetRenderView()->GetViewRenderer()->CreateTextureWithResource(uRcid);
    m_pTexture = pTexture;
    m_pTexture->Retain();
    SetFrameRect(rt);
    return pTexture?this:nullptr;
}
//从内存中创建
S2SpriteFrame *S2SpriteFrame::CreateWithMemory(const S2Data data, const S2uInt length, const S2Rect *rt)
{
    __ReleaseTexture();
    auto pTexture = S2Director::GetInstance()->GetRenderView()->GetViewRenderer()->CreateTextureWithMemory(data, length);
    m_pTexture = pTexture;
    m_pTexture->Retain();
    SetFrameRect(rt);
    return pTexture?this:nullptr;
}

//设置获取纹理
void S2SpriteFrame::SetTexture(S2Texture *pTexture)
{
    //对之前纹理进行释放
    __ReleaseTexture();
    m_pTexture = pTexture;
    m_pTexture->Retain();
}
const S2Texture *S2SpriteFrame::GetTexture()const
{
    return m_pTexture;
}

//设置裁剪区
void S2SpriteFrame::SetFrameRect(const S2Rect *rt)
{
        if (rt)
        {
            m_frameRect = *rt;
        }
        else
        {
            m_frameRect.left = 0;
            m_frameRect.top = 0;
            m_frameRect.right = m_frameRect.left + m_pTexture ? m_pTexture->GetWidth() : 0;
            m_frameRect.bottom = m_frameRect.top + m_pTexture ? m_pTexture->GetHeight() : 0;
        }
}
const S2Rect &S2SpriteFrame::GetFrameRect() const
{
    return m_frameRect;
}

//获取设置帧宽高
void S2SpriteFrame::SetFrameWidth(int nWidth)
{
    m_frameRect.right = m_frameRect.left + nWidth;
}
int S2SpriteFrame::GetFrameWidth()const
{
    return m_frameRect.right - m_frameRect.left;
}
void S2SpriteFrame::SetFrameHeight(int nHeight)
{
    m_frameRect.bottom = m_frameRect.top + nHeight;
}
int S2SpriteFrame::GetFrameHeight()const
{
    return m_frameRect.bottom - m_frameRect.top;
}

void S2SpriteFrame::__ReleaseTexture()
{
    S2SAFERELEASE(m_pTexture);
}