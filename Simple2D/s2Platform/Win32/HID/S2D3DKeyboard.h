#ifndef _S2D3DKEYBOARD_H_
#define _S2D3DKEYBOARD_H_
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "../../../s2Protocol/S2HIDProtocol.h"

class S2D3DKeyboard : public S2MouseProtocol
{
public:
    S2D3DKeyboard();
    ~S2D3DKeyboard();
public:
    S2D3DKeyboard *CreateWithHandle(HWND hWnd, HINSTANCE hInstance, DWORD keyboardCoopFlags);
public:
	bool				GetInput();   //用于获取输入信息的函数
	bool				IsKeyDown(int iKey);   //判断键盘上某键是否按下
private:
	IDirectInput8					*m_pDirectInput;    //IDirectInput8接口对象
	IDirectInputDevice8		        *m_pKeyboardDevice;  //键盘设备接口对象
	char						    m_keyBuffer[256];   //用于键盘键值存储的数组
};
#endif