/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-03 17:40:29 
 * @Brief: 鼠标输入
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-15 15:53:27
 * @Last Modified log: 
 */
#ifndef _S2MOUSE_H_
#define _S2MOUSE_H_
#include "../s2Protocol/S2HIDProtocol.h"
#include "../s2Core/S2Object.h"
class S2MouseProtocol;
class S2Mouse : public S2Object
{
public:
    S2Mouse(S2MouseProtocol *pProtocal);
    ~S2Mouse();
public:
    //取得输入信息-轮询检查
    bool GetInput();

    //鼠标按键是否被按下
    bool IsMouseDown(S2MouseProtocol::MouseButtonDirection vButtom);

    //获取鼠标相对值
    S2Vector3 GetMouseDXYZ();
private:
    S2MouseProtocol *m_pMouseProtocal;
};
#endif