/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-08 22:06:18 
 * @Brief: 特效实现类
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-08 22:10:01
 * @Last Modified log: 
 */
#include "S2Effect.h"
#include "S2Renderer.h"
S2Effect::S2Effect(S2Renderer *pRenderer)
{

    m_pRenderer = pRenderer;
    m_pRenderer->Retain();
    
}
S2Effect::~S2Effect()
{
    S2SAFERELEASE(m_pRenderer);
}

S2Renderer *S2Effect::GetRenderer()const
{
    return m_pRenderer;
}