#include "SEvent.h"
#include "SEventFlag.h"
SEvent::Type SEvent::GetType()const
{
    return m_unType;
}
bool SEvent::SetType(SEvent::Type type)
{
    if(!m_bIsAdded)
        m_unType = type;
    return !m_bIsAdded;
}
//取得事件源
void *SEvent::GetSender() const
{
    return m_pSender;
}
bool SEvent::SetSender(void *pSender)
{
    if(!m_bIsAdded)
        m_pSender = pSender;
    return !m_bIsAdded;
}

int SEvent::GetPriority()const
{
    return m_nPriority;
}
bool SEvent::SetPriority(int nPriority)
{
    if(!m_bIsAdded)
        m_nPriority = nPriority;
    return !m_bIsAdded;
}
//事件能否往下传递
bool SEvent::GetDelivery()const
{
    return SEventFlag::HaveFlag(m_flag,SEventFlag::OnceDelivery);
}
void SEvent::SetDelivery(bool bDelivery)
{
    SEventFlag::SetFlag(m_flag,SEventFlag::OnceDelivery,!bDelivery);
}

//取得自定义数据
void SEvent::SetUserData(const void *pUserData, bool bBind)
{
    m_pUserData = (void *)pUserData;
    SEventFlag::SetFlag(m_flag, SEventFlag::BindUserData, bBind);

}
void *SEvent::GetUserData() const
{
    return m_pUserData;
}

 SEvent *SEvent::AutoRelease(bool bRelease)
  {
     SEventFlag::SetFlag(m_flag,SEventFlag::AutoRelease,bRelease);
     return this;
  }

SEvent::SEvent(SEvent::Type type, void *pSender, void *pUserData)
:m_unType(type),m_pSender(pSender),m_bIsAdded(false),m_flag(0),m_nPriority(2147483647),m_pUserData(pUserData)
{
    
}
SEvent::~SEvent()
{
    
}
