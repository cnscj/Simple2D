/**
* @Author: cnscj
* @Version: v1.0
* @Date: 2018-04-05 16:05:40
* @Brief: 鼠标事件监听者
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-04 12:43:59
* @Last Modified log:
*/
#ifndef _S2MOUSEEVENTLISTENER_H_
#define _S2MOUSEEVENTLISTENER_H_
#include "S2BaseEventListener.h"
class S2MouseEvent;
class S2MousemEventListener : public S2BaseEventListener
{
public:
    S2MousemEventListener();
    ~S2MousemEventListener();
public:
    SEventListener::Handler<bool(S2MouseEvent *)>          OnMouseDown;
    SEventListener::Handler<void(S2MouseEvent *)>          OnMouseMove;
    SEventListener::Handler<void(S2MouseEvent *)>          OnMouseUp;
    SEventListener::Handler<void(S2MouseEvent *)>          OnMouseScroll;
protected:
    virtual void OnEvent(SEvent *pEvent);

};


#endif