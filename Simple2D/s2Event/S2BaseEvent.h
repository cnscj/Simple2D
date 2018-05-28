#ifndef _S2BASEEVENT_H_
#define _S2BASEEVENT_H_
#include "../s2Base/sDispatch/SEvent.h"
#include "../s2Core/S2Object.h"
class S2BaseEvent :
    public SEvent,
    public S2Object
{
protected:
    S2BaseEvent(SEvent::Type type, void *pSender = nullptr, void *pUserData = nullptr) :SEvent(type, pSender, pUserData){}
    virtual ~S2BaseEvent(){}
};

#endif