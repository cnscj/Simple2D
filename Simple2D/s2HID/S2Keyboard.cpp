/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-15 12:46:50 
 * @Brief: 键盘控制器实现
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-15 15:53:25
 * @Last Modified log: 
 */
#include "../s2Event/S2KeyboardEvent.h"
#include "S2Keyboard.h"

S2Keyboard::S2Keyboard(S2KeyboardProtocol *pProtocal)
:m_pKeyboardProtocal(pProtocal)
{

}
S2Keyboard::~S2Keyboard()
{

}

    //取得输入信息-轮询检查
bool S2Keyboard::GetInput()
{
   return m_pKeyboardProtocal->GetInput();
}

    //键盘按键是否被按下
bool S2Keyboard::IsKeyDown(S2Word vKey)
{
    return m_pKeyboardProtocal->IsKeyDown(vKey);
}