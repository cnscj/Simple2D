/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-04 13:31:58 
 * @Brief: 命令事件
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-04 22:33:48
 * @Last Modified log: 
 */

#ifndef _S2COMMANDEVENT_H_
#define _S2COMMANDEVENT_H_
#include "S2BaseEvent.h"
class S2CommandEvent : public S2BaseEvent
{
public:
    S2CommandEvent();
    S2CommandEvent(const S2uInt command,void *pSender=nullptr, void *pUserData=nullptr);
    ~S2CommandEvent();
public:
    void SetCommand(S2uInt command);
    S2uInt GetCommand() const;

private:
    S2uInt         m_command;            //自定义类型
};
#endif
