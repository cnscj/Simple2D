/**
 * @Author: Minalien 
 * @Version: v1.0 
 * @Date: 2008-06-13 00:00:00 
 * @Brief: XBox控制器输入设备
 * @link https://www.codeproject.com/Articles/26949/Xbox-Controller-Input-in-C-with-XInput
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-15 14:28:07
 * @Last Modified log: 
 */

/*
//以下是方向十字键
XINPUT_GAMEPAD_DPAD_UP          0x00000001
XINPUT_GAMEPAD_DPAD_DOWN        0x00000002
XINPUT_GAMEPAD_DPAD_LEFT        0x00000004
XINPUT_GAMEPAD_DPAD_RIGHT       0x00000008
//以下是控制键
XINPUT_GAMEPAD_START            0x00000010
XINPUT_GAMEPAD_BACK             0x00000020
//扳机键
XINPUT_GAMEPAD_LEFT_THUMB       0x00000040
XINPUT_GAMEPAD_RIGHT_THUMB      0x00000080
XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100
XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200
//普通按键
XINPUT_GAMEPAD_A                0x1000
XINPUT_GAMEPAD_B                0x2000
XINPUT_GAMEPAD_X                0x4000
XINPUT_GAMEPAD_Y                0x8000
//

*/

#ifndef _S2D3DJOYPAD_H_
#define _S2D3DJOYPAD_H_

#include <Windows.h>
#include <XInput.h>
#include "../../../s2Protocol/S2HIDProtocol.h"

#pragma comment(lib, "XInput.lib")
#define WIN32_LEAN_AND_MEAN

class S2D3DJoypad : public S2JoypadProtocol
{
public:
    const static int MIN_THUMB_VALUE = -10000;
    const static int MAX_THUMB_VALUE = 10000;
public:
    S2D3DJoypad();
    ~S2D3DJoypad();
public:
    //取得输入信息
    bool GetInput();
    //控制器震动
    void Vibrate(int leftVal = 50, int rightVal = 50);

    //按键触发
    bool IsButtonDown(S2Word wButtom);
    //扳机触发
    bool IsTriggerDown(JoypadDirection whichT);
    //摇杆触发-返回方位
    S2Point GetThumbPos(JoypadDirection whichT);

    bool IsThumbMove(JoypadDirection dpaddir, JoypadDirection whichdir, int nMin = MIN_THUMB_VALUE, int nMax = MAX_THUMB_VALUE);
    int GetThumbX(JoypadDirection whichT);
    int GetThumbY(JoypadDirection whichT);
private:
    static int sm_nController;					//全局控制器数量
    XINPUT_STATE m_sControllerState;			//控制器状态
    int m_nControllerNum;						//控制器编号
};
#endif