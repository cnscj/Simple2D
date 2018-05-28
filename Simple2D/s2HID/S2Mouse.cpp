/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-15 12:46:20 
 * @Brief: 鼠标控制器实现
 * @Last Modified by: cnscj 
 * @Last Modified time: 2018-05-15 12:46:20 
 * @Last Modified log: 
 */

#include "../s2Event/S2MouseEvent.h"
#include "S2Mouse.h"

S2Mouse::S2Mouse(S2MouseProtocol *pProtocal)
:m_pMouseProtocal(pProtocal)
{

}
S2Mouse::~S2Mouse()
{

}

//取得输入信息-轮询检查
bool S2Mouse::GetInput()
{
    return m_pMouseProtocal->GetInput();
}


//鼠标按键是否被按下
bool S2Mouse::IsMouseDown(S2MouseProtocol::MouseButtonDirection vButtom)
{
    return m_pMouseProtocal->IsMouseDown(vButtom);
}

S2Vector3 S2Mouse::GetMouseDXYZ()
{
    return m_pMouseProtocal->GetMouseDXYZ();
}