/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-08 22:12:33 
 * @Brief: 模板缓存类
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-08 22:13:53
 * @Last Modified log: 
 */

#include "S2StencilBuffer.h"
#include "S2Renderer.h"
S2StencilBuffer::S2StencilBuffer(S2Renderer *pRenderer)
{
    m_pRenderer = pRenderer;
    m_pRenderer->Retain();
}
S2StencilBuffer::~S2StencilBuffer()
{
    S2SAFERELEASE(m_pRenderer);
}

//取得渲染器
S2Renderer *S2StencilBuffer::GetRenderer()const
{
    return m_pRenderer;
}