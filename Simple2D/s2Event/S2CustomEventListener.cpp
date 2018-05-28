#include "S2CustomEventListener.h"
#include "S2CustomEvent.h"
#include "S2EventTable.h"
S2CustomEventListener::S2CustomEventListener(S2CustomHandler handler)
:S2BaseEventListener(S2EventTable::System::CustomEvent), OnHandler(handler)
{
    
}
S2CustomEventListener::~S2CustomEventListener()
{
    
}

void S2CustomEventListener::OnEvent(SEvent *pEvent)
{
    S2CustomEvent *e = static_cast<S2CustomEvent *>(pEvent);
    
    OnHandler(e->GetCustomEvent(),e->GetSender(),e->GetUserData());
}
