#ifndef _S2BASEEVENTLISTENER_H_
#define _S2BASEEVENTLISTENER_H_
#include "../s2Base/sDispatch/SEventListener.h"
#include "../s2Core/S2Object.h"
class S2BaseEventListener :
    public SEventListener,
    public S2Object
{
protected:
    S2BaseEventListener(SEvent::Type type, SEventListener::Handler<void(SEvent *)> lamdba = [](SEvent *){}) :SEventListener(type, lamdba){}
    virtual ~S2BaseEventListener(){}
};

#endif