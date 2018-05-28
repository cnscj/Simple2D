/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-24 09:01:51 
 * @Brief: 键盘事件监听
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-04 12:49:12
 * @Last Modified log: 
 */
#ifndef _S2KEYBOARDEVENTLISTENER_H_
#define _S2KEYBOARDEVENTLISTENER_H_
#include "S2BaseEventListener.h"
class S2KeyboardEvent;
class S2KeyboardEventListener : public S2BaseEventListener
{
public:
    S2KeyboardEventListener();
    ~S2KeyboardEventListener();
public:
    SEventListener::Handler<bool(S2KeyboardEvent *)>          OnKeyPress;
    SEventListener::Handler<bool(S2KeyboardEvent *)>          OnKeyRelease;
protected:
    virtual void OnEvent(SEvent *pEvent);

};


#endif