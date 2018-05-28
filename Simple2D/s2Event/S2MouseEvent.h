/**
 * @Author: cnscj
 * @Version: v1.0
 * @Date: 2018-04-05 16:05:40
 * @Brief: 鼠标消息
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-23 22:01:06
 * @Last Modified log:
 */

#ifndef _S2MOUSEEVENT_H_
#define _S2MOUSEEVENT_H_
#include "S2BaseEvent.h"
class S2MouseEvent : public S2BaseEvent
{
public:
    enum class Type
    {
        Dowm,
        Move,
        Up,
        Scroll,
    };
public:
    S2MouseEvent(Type mouseType, void *pSender = nullptr);
    ~S2MouseEvent();

public:
    long mouseButton;
    long mouseX;
    long mouseY;
    long mouseScroll;

    Type eType;             //鼠标的事件类型
};
#endif