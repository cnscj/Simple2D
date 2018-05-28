/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-03 17:31:05 
 * @Brief: 键盘输入
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-15 12:47:35
 * @Last Modified log: 
 */
#ifndef _S2KEYBOARD_H_
#define _S2KEYBOARD_H_
#include "../s2Protocol/S2HIDProtocol.h"
#include "../s2Core/S2Object.h"
class S2KeyboardProtocol;
class S2Keyboard : public S2Object
{
public:
    S2Keyboard(S2KeyboardProtocol *pProtocal);
    ~S2Keyboard();
public:
    //取得输入信息-轮询检查
    bool GetInput();

	//键盘按键是否被按下
	virtual bool IsKeyDown(S2Word vKey);

private:
    S2KeyboardProtocol *m_pKeyboardProtocal;
};
#endif