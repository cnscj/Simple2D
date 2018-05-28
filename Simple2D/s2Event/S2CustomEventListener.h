/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-04 13:55:20 
 * @Brief: 自定义监听者
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-04 14:25:11
 * @Last Modified log: 
 */
#ifndef _S2CUSTOMEVENTLISTENER_H_
#define _S2CUSTOMEVENTLISTENER_H_
#include "S2BaseEventListener.h"
class S2CustomEvent;
class S2CustomEventListener : public S2BaseEventListener
{
    typedef SEventListener::Handler<void( S2String, void *,void *)> S2CustomHandler;
public:
    S2CustomEventListener(S2CustomHandler handler = []( S2String event,void *sender, void *pData){});
    ~S2CustomEventListener();
public:
    //回调函数
    S2CustomHandler   OnHandler;
protected:
    //事件处理
    virtual void OnEvent(SEvent *pEvent);
};

#endif
