#include "S2EventTable.h"
#include "S2EventUtil.h"

const SEvent::Type S2EventTable::System::CustomEvent = S2EventUtil::GetEventUID();
const SEvent::Type S2EventTable::System::CommandEvent = S2EventUtil::GetEventUID();
const SEvent::Type S2EventTable::System::MouseEvent = S2EventUtil::GetEventUID();
const SEvent::Type S2EventTable::System::KeyboardEvent = S2EventUtil::GetEventUID();
const SEvent::Type S2EventTable::System::JoyStickEvent = S2EventUtil::GetEventUID();
const SEvent::Type S2EventTable::System::RenderEvent = S2EventUtil::GetEventUID();
const SEvent::Type S2EventTable::System::UpdateEvent = S2EventUtil::GetEventUID();

const S2uInt S2EventTable::Command::CallbackExec = S2EventUtil::GetCommandUID();
const S2uInt S2EventTable::Command::ObjectRelease = S2EventUtil::GetCommandUID();
const S2uInt S2EventTable::Command::JoypadVibrate = S2EventUtil::GetCommandUID();