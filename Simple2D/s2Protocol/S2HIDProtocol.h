/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-19 15:18:50 
 * @Brief: 人体学接口设备协议文件
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-19 15:26:18
 * @Last Modified log: 
 */
#ifndef _S2HIDPROTOCOL_H_
#define _S2HIDPROTOCOL_H_
#include "../s2Core/S2Global.h"

/**
* @brief 摇杆控制器协议
*
*/
class S2JoystickProtocol
{
public:

};

/**
* @brief 手柄控制器协议
* 
*/
class S2JoypadProtocol
{
public:
    enum class JoypadDirection
    {
        None,       //无方向
        Left,       //左
        Right,      //右
        Up,         //上
        Down        //下
    };

public:

    //取得输入信息-轮询检查
    virtual bool GetInput() = 0;

    //控制器震动
    virtual void Vibrate(int leftVal, int rightVal){};

    //按键触发
    virtual bool IsButtonDown(S2Word wButtom) = 0;

    //扳机触发
    virtual bool IsTriggerDown(JoypadDirection dir) = 0;

    //取得摇杆坐标
    virtual S2Point GetThumbPos(JoypadDirection dir) = 0;

};


/**
* @brief 键盘控制器协议
* 
*/
class S2KeyboardProtocol
{
public:
    //取得输入信息-轮询检查
    virtual bool GetInput() = 0;

    //键盘按键是否被按下
    virtual bool IsKeyDown(S2Word vKey) = 0;
};


/**
* @brief 鼠标控制器
* 
*/
class S2MouseProtocol
{
public:
    enum class MouseButtonDirection
    {
        Left,               //左
        Middle,             //中
        Right,              //右
    };
public:
    //取得输入信息-轮询检查
    virtual bool GetInput() = 0;

    //鼠标按键是否被按下
    virtual bool IsMouseDown(MouseButtonDirection vButtom) = 0;

    //获取鼠标相对值
    virtual S2Vector3 GetMouseDXYZ();

};



#endif