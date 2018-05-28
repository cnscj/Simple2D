/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-04 22:31:19 
 * @Brief: 命令监听
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-04 22:36:51
 * @Last Modified log: 
 */
#include "S2CommandEventListener.h"
#include "S2CommandEvent.h"
#include "S2EventTable.h"
S2CommandEventListener::S2CommandEventListener(S2CommandHandler handler)
:S2BaseEventListener(S2EventTable::System::CommandEvent), OnHandler(handler)
{
    
}
S2CommandEventListener::~S2CommandEventListener()
{
    
}

void S2CommandEventListener::OnEvent(SEvent *pEvent)
{
    S2CommandEvent *e = static_cast<S2CommandEvent *>(pEvent);
    
    OnHandler(e->GetCommand(),e->GetSender(),e->GetUserData());
}
