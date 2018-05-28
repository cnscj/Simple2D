#include "S2Device.h"
#include "S2Renderer.h"

//返回缓冲区宽度
int S2Device::GetBufferWidth()const
{
    //TODO:
    return 0;
}

//返回缓冲区高度
int S2Device::GetBufferHeight()const
{
    //TODO:
    return 0;
}

//返回缓冲区深度
int S2Device::GetBfferDepth()const
{
    //TODO:
    return 0;
}

S2Renderer *S2Device::GetRenderer()const
{
    return m_pRenderer;
}

S2Device::S2Device(S2Renderer *pRenderer)
{
    m_pRenderer = pRenderer;
    m_pRenderer->Retain();
}
S2Device::~S2Device()
{
    S2SAFERELEASE(m_pRenderer);
}