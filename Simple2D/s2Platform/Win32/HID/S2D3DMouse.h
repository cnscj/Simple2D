#ifndef _S2D3DMOUSE_H_
#define _S2D3DMOUSE_H_
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "../../../s2Protocol/S2HIDProtocol.h"

class S2D3DMouse : public S2MouseProtocol
{
public:
    S2D3DMouse();
    ~S2D3DMouse();
public:
    S2D3DMouse *CreateWithHandle(HWND hWnd, HINSTANCE hInstance, DWORD mouseCoopFlags);
public:
    bool				GetInput();   //用于获取输入信息的函数
    bool				IsMouseButtonDown(int button);  //判断鼠标按键是否被按下
    S2Vector3           GetMouseDXYZ();

	float				GetMouseDX();   //返回鼠标的X轴坐标值
	float				GetMouseDY();	//返回鼠标的Y轴坐标值
	float				GetMouseDZ();	//返回鼠标的Z轴坐标值

private:
    IDirectInput8				*m_pDirectInput;    //IDirectInput8接口对象
    IDirectInputDevice8		    *m_mouseDevice;         //鼠标设备接口对象
    DIMOUSESTATE				m_mouseState;			//用于鼠标键值存储的一个结构体
};
#endif