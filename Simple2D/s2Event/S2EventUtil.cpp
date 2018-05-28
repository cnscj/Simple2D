#include "S2EventUtil.h"
SEvent::Type S2EventUtil::sm_eventUids = 0;
S2uInt S2EventUtil::sm_commandUids = 0;
/////////////////
SEvent::Type S2EventUtil::GetEventUID()
{
    return ++sm_eventUids;
}
S2uInt S2EventUtil::GetCommandUID()
{
    return ++sm_commandUids;
}
