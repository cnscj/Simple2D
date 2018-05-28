/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-04 22:31:03 
 * @Brief:命令事件实现
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-04 22:35:16
 * @Last Modified log: 
 */
#include "S2CommandEvent.h"
#include "S2EventTable.h"
S2CommandEvent::S2CommandEvent()
:S2BaseEvent(S2EventTable::System::CommandEvent), m_command(0)
{
    
}
S2CommandEvent::S2CommandEvent(const S2uInt command, void *pSender, void *pUserData)
: S2BaseEvent(S2EventTable::System::CommandEvent, pSender, pUserData), m_command(command)
{
    
}
S2CommandEvent::~S2CommandEvent()
{
    
}

void S2CommandEvent::SetCommand(S2uInt command)
{
    m_command = command;
}
S2uInt S2CommandEvent::GetCommand() const
{
    return m_command;
}
