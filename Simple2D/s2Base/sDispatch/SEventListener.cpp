#include "SEventListener.h"
#include "SEventFlag.h"

SEventListener::SEventListener(SEvent::Type type,SEventListener::Handler<void(SEvent *)> lamdba)
:m_type(type),m_pDispatcher(nullptr),m_flag(0),m_lamHandler(lamdba),m_nPriority(2147483647)
{
    
}
SEventListener::~SEventListener()
{
    
}

const SEvent::Type &SEventListener::GetType() const
{
    return m_type;
}
bool SEventListener::SetType(const SEvent::Type type)
{
    if(!m_pDispatcher)
        m_type = type;
    return !m_pDispatcher;
}
//监听器的源
const void *SEventListener::GetSource() const
{
    return m_pSource;
}
bool SEventListener::SetSource(void *pSource)
{
    if(!m_pDispatcher)
        m_pSource = pSource;
    return !m_pDispatcher;
}
const void *SEventListener::GetDispatcher() const
{
    return m_pDispatcher;
}

int SEventListener::GetPriority() const
{
    return m_nPriority;
}
void SEventListener::SetPriority(int nPriority)
{
    if(m_pDispatcher){
        m_nPriority = nPriority;
        SEventFlag::AddFlag(m_flag,SEventFlag::ReOrder);
    }else m_nPriority = nPriority;
}

void SEventListener::OnEvent(SEvent *pEvent)
{
    m_lamHandler(pEvent);
}

//事件处理完毕
void SEventListener::OnFinish(SEvent *pEvent)
{
    
}

void SEventListener::OnHandle(SEvent *pEvent)
{
    OnEvent(pEvent);
    OnFinish(pEvent);
}
