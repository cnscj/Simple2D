/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-23 18:46:26 
 * @Brief: 鼠标事件实现
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-23 19:09:26
 * @Last Modified log: 
 */
#include "S2MouseEvent.h"
#include "S2EventTable.h"


S2MouseEvent::S2MouseEvent(Type mouseType, void *pSender)
:S2BaseEvent(S2EventTable::System::MouseEvent, pSender), eType(mouseType)
{

}
S2MouseEvent::~S2MouseEvent()
{

}
