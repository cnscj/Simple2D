/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-15 12:46:56 
 * @Brief: 摇杆控制器实现
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-15 13:25:41
 * @Last Modified log: 
 */
#include "../s2Protocol/S2HIDProtocol.h"
#include "../s2Event/S2CommandEventListener.h"
#include "../s2Event/S2JoypadEvent.h"
#include "../s2Event/S2EventTable.h"
#include "../s2Engine/S2Application.h"
#include "S2Joypad.h"

S2Joypad::S2Joypad(S2JoypadProtocol *pProtocol)
:m_pJoypadProtocol(pProtocol)
{
    m_pCommandEventListener = new S2CommandEventListener();
    m_pCommandEventListener->OnHandler = [=](const S2uInt command, void *sender, void *pData)
    {
        if (command == S2EventTable::Command::JoypadVibrate)
        {
            auto pValue = static_cast<S2Point *>(pData);
            if (pValue)
            {
                Vibrate(pValue->x, pValue->y);
            }
            else Vibrate(100, 100);
        }
    };
    S2Application::GetInstance()->GetDispatcher()->AddEventListener(m_pCommandEventListener);
}
S2Joypad::~S2Joypad()
{
    S2Application::GetInstance()->GetDispatcher()->RemoveEventListener(m_pCommandEventListener);
}

//取得输入信息-轮询检查
bool S2Joypad::GetInput()
{
    return m_pJoypadProtocol->GetInput();
}

//控制器震动
void S2Joypad::Vibrate(int leftVal, int rightVal)
{
    return m_pJoypadProtocol->Vibrate(leftVal, rightVal);
}

//按键触发
bool S2Joypad::IsButtonDown(S2Word wButtom)
{
    return m_pJoypadProtocol->IsButtonDown(wButtom);
}

//扳机触发
bool S2Joypad::IsLeftTriggerDown()
{
    return m_pJoypadProtocol->IsTriggerDown(S2JoypadProtocol::JoypadDirection::Left);
}

//扳机触发
bool S2Joypad::IsRightTriggerDown()
{
    return m_pJoypadProtocol->IsTriggerDown(S2JoypadProtocol::JoypadDirection::Right);
}

//取得摇杆坐标
S2Point S2Joypad::GetLeftThumbPos()
{
    return m_pJoypadProtocol->GetThumbPos(S2JoypadProtocol::JoypadDirection::Left);
}

//取得摇杆坐标
S2Point S2Joypad::GetRightThumbPos()
{
    return m_pJoypadProtocol->GetThumbPos(S2JoypadProtocol::JoypadDirection::Right);
}