/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-28 23:53:02 
 * @Brief: 音频引擎实现类
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-28 23:57:39
 * @Last Modified log: 
 */
#include "S2AudioSystem.h"

S2BaseAudio *S2AudioSystem::GetAudio()const
{ 
    return m_pService;
}

void S2AudioSystem::Provide(S2BaseAudio* service)
{
    if (m_pService == nullptr)
    {
        // 退回空服务
        m_pService = &m_nullService;
    }
    else
    {
        m_pService = service;
    }
}

S2AudioSystem::S2AudioSystem()
:m_pService(&m_nullService)
{

}
S2AudioSystem::~S2AudioSystem()
{

}