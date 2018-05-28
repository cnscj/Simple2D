/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-03 17:33:44 
 * @Brief: 摇杆类
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-15 12:51:17
 * @Last Modified log: 
 */
#ifndef _S2JOYPAD_H_
#define _S2JOYPAD_H_

#include "../s2Core/S2Object.h"

class S2JoypadProtocol;
class S2CommandEventListener;

class S2Joypad : public S2Object
{
public:
    S2Joypad(S2JoypadProtocol *pProtocol);
    ~S2Joypad();
public:
    //取得输入信息-轮询检查
	bool GetInput();
	
	//控制器震动
	void Vibrate(int leftVal, int rightVal);

	//按键触发
	bool IsButtonDown(S2Word wButtom);

	//扳机触发
    bool IsLeftTriggerDown();

    //扳机触发
    bool IsRightTriggerDown();

	//取得摇杆坐标
    S2Point GetLeftThumbPos();

    //取得摇杆坐标
    S2Point GetRightThumbPos();
private:
    S2JoypadProtocol        *m_pJoypadProtocol;             //手柄协议
    S2CommandEventListener  *m_pCommandEventListener;       //手柄命令
};
#endif