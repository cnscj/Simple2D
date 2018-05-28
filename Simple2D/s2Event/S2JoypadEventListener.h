/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-04 12:23:21 
 * @Brief: 手柄监听器
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-04 12:43:33
 * @Last Modified log: 
 */
#ifndef _S2JOYPADEVENTLISTENER_H_
#define _S2JOYPADEVENTLISTENER_H_
#include "S2BaseEventListener.h"
class S2JoypadEvent;
class S2JoypadEventListener : public S2BaseEventListener
{
public:
    S2JoypadEventListener();
    ~S2JoypadEventListener();
public:
    SEventListener::Handler<void(S2JoypadEvent *)>          OnVibrate;
    SEventListener::Handler<void(S2JoypadEvent *)>          OnButtonDown;
    SEventListener::Handler<void(S2JoypadEvent *)>          OnTriggerDown;
    SEventListener::Handler<void(S2JoypadEvent *)>          OnThumbMove;

protected:
    virtual void OnEvent(SEvent *pEvent);

};


#endif