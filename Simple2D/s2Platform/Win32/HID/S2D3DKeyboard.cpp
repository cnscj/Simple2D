#include "S2D3DKeyboard.h"

S2D3DKeyboard::S2D3DKeyboard()
{

}
S2D3DKeyboard::~S2D3DKeyboard()
{
	if(m_pKeyboardDevice != NULL)
		m_pKeyboardDevice->Unacquire();
	S2SAFERELEASE(m_pKeyboardDevice);
    S2SAFERELEASE(m_pDirectInput);
}

S2D3DKeyboard *S2D3DKeyboard::CreateWithHandle(HWND hWnd, HINSTANCE hInstance, DWORD keyboardCoopFlags)
{
	//初始化一个IDirectInput8接口对象
    if (::DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL) == S_OK)
    {
	    //进行键盘设备的初始化
        if (m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pKeyboardDevice, NULL) == S_OK)
        {
            m_pKeyboardDevice->SetCooperativeLevel(hWnd, keyboardCoopFlags);
            m_pKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
            m_pKeyboardDevice->Acquire();
            m_pKeyboardDevice->Poll();

            return this;
        }
    }

	return nullptr;
}

//-----------------------------------------------------------------------------
// Name：DInputClass::GetInput()
// Desc: 用于获取输入信息的函数
//-----------------------------------------------------------------------------
bool S2D3DKeyboard::GetInput()
{
	HRESULT hr = m_pKeyboardDevice->GetDeviceState(sizeof(m_keyBuffer), (void**)&m_keyBuffer); 
	//获取键盘输入消息
    if (hr == S_OK)
	{
		m_pKeyboardDevice->Acquire();  
		m_pKeyboardDevice->GetDeviceState( sizeof(m_keyBuffer),(LPVOID)m_keyBuffer );

        return true;
	}
    return false;
}

//-----------------------------------------------------------------------------
// Name：DInputClass::IsKeyDown()
// Desc: 判断键盘上某个键是否按下
//-----------------------------------------------------------------------------
bool S2D3DKeyboard::IsKeyDown(int iKey)
{
	if(m_keyBuffer[iKey] & 0x80)
		return true;
	else
		return false;
}
