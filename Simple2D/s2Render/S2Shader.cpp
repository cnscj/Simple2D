/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-08 22:10:51 
 * @Brief: 着色器实现
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-08 22:13:45
 * @Last Modified log: 
 */
#include "S2Shader.h"
#include "S2Renderer.h"
S2Shader::S2Shader(S2Renderer *pRenderer)
{
    m_pRenderer = pRenderer;
    m_pRenderer->Retain();
}
S2Shader::~S2Shader()
{
    S2SAFERELEASE(m_pRenderer);
}

S2Renderer *S2Shader::GetRenderer()const
{
    return m_pRenderer;
}