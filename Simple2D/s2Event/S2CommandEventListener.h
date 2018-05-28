/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-04 13:31:34 
 * @Brief: 命令事件监听器
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-04 13:41:21
 * @Last Modified log: 
 */
#ifndef _S2COMMANDEVENTLISTENER_H_
#define _S2COMMANDEVENTLISTENER_H_
#include "S2BaseEventListener.h"
class S2CommandEvent;
class S2CommandEventListener : public S2BaseEventListener
{
    typedef SEventListener::Handler<void(const S2uInt, void *, void *)> S2CommandHandler;
public:
    S2CommandEventListener(S2CommandHandler handler = [](const S2uInt command, void *sender, void *pData){});
    ~S2CommandEventListener();
public:
    //回调函数
    S2CommandHandler   OnHandler;
protected:
    //事件处理
    virtual void OnEvent(SEvent *pEvent);
};

#endif