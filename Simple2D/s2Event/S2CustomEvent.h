/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-04 13:55:40 
 * @Brief: 自定义消息
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-04 13:58:19
 * @Last Modified log: 
 */

#ifndef _S2CUSTOMEVENT_H_
#define _S2CUSTOMEVENT_H_
#include "S2BaseEvent.h"
class S2CustomEvent : public S2BaseEvent
{
public:
    S2CustomEvent();
    S2CustomEvent(S2String event,void *pSender=nullptr, void *pUserData=nullptr);
    ~S2CustomEvent();
public:
    void SetCustomEvent(S2String event);
    const S2String &GetCustomEvent() const;

private:
    S2String         m_strCustomEvent;            //自定义类型
};
#endif
