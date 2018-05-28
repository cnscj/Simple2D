/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-23 18:35:54 
 * @Brief: 事件类型
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-19 14:08:50
 * @Last Modified log: 
 */

#ifndef _S2EVENTTABLE_H_
#define _S2EVENTTABLE_H_
#include "../s2Base/sDispatch/SEvent.h"
#include "../s2Core/S2Global.h"

namespace S2EventTable
{
    //系统事件
    namespace System
    {
        extern const SEvent::Type CustomEvent;          //用户自定义事件
        extern const SEvent::Type CommandEvent;         //系统命令事件
        extern const SEvent::Type MouseEvent;           //鼠标事件
        extern const SEvent::Type KeyboardEvent;        //键盘事件
        extern const SEvent::Type JoyStickEvent;        //摇杆事件
        extern const SEvent::Type RenderEvent;          //渲染事件
        extern const SEvent::Type UpdateEvent;          //更新事件
    };

    //命令事件
    namespace Command
    {
        extern const S2uInt CallbackExec;                //回调执行
        extern const S2uInt ObjectRelease;               //对象释放
        extern const S2uInt JoypadVibrate;             //摇杆震动

    };

};
#endif