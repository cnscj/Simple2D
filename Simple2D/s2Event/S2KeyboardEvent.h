/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-24 09:01:36 
 * @Brief:键盘事件监听器
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-04 12:51:33
 * @Last Modified log: 
 */
#ifndef _S2KEYBOARDEVENT_H_
#define _S2KEYBOARDEVENT_H_
#include "S2BaseEvent.h"
class S2KeyboardEvent : public S2BaseEvent
{
public:
    S2KeyboardEvent(void *pSender = nullptr);
    ~S2KeyboardEvent();

private:

};
#endif
