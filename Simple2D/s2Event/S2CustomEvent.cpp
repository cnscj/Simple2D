#include "S2CustomEvent.h"
#include "S2EventTable.h"
S2CustomEvent::S2CustomEvent()
:S2BaseEvent(S2EventTable::System::CustomEvent), m_strCustomEvent("")
{
    
}
S2CustomEvent::S2CustomEvent(S2String event,void *pSender, void *pUserData)
:S2BaseEvent(S2EventTable::System::CustomEvent, pSender, pUserData), m_strCustomEvent(event)
{
    
}
S2CustomEvent::~S2CustomEvent()
{
    
}

void S2CustomEvent::SetCustomEvent(S2String event)
{
    m_strCustomEvent = event;
}
const S2String &S2CustomEvent::GetCustomEvent() const
{
    return m_strCustomEvent;
}
