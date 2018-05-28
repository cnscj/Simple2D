/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-15 14:06:53 
 * @Brief: D3D鼠标监听实现
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-15 14:34:23
 * @Last Modified log: 
 */
#include "S2D3DMouse.h"
S2D3DMouse::S2D3DMouse()
{

}
S2D3DMouse::~S2D3DMouse()
{
	if(m_mouseDevice != NULL)
		m_mouseDevice->Unacquire();
    S2SAFERELEASE(m_mouseDevice);
    S2SAFERELEASE(m_pDirectInput);
}
S2D3DMouse *S2D3DMouse::CreateWithHandle(HWND hWnd, HINSTANCE hInstance, DWORD mouseCoopFlags)
{
	//初始化一个IDirectInput8接口对象
    if (::DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL) == S_OK)
    {
	    //进行鼠标设备的初始化
        if (m_pDirectInput->CreateDevice(GUID_SysMouse, &m_mouseDevice, NULL) == S_OK)
        {
	        m_mouseDevice->SetCooperativeLevel( hWnd,mouseCoopFlags);
	        m_mouseDevice->SetDataFormat( &c_dfDIMouse );
	        m_mouseDevice->Acquire();
            m_mouseDevice->Poll();

            return this;
        }

    }
    return nullptr;
}

//-----------------------------------------------------------------------------
// Name：DInputClass::GetInput()
// Desc: 用于获取输入信息的函数
//-----------------------------------------------------------------------------
bool S2D3DMouse::GetInput()
{
    HRESULT hr = m_mouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (void**)&m_mouseState);
	//获取鼠标输入消息
	if(hr == S_OK)
	{
		m_mouseDevice->Acquire();
        m_mouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (void**)&m_mouseState);

        return true;
	}
    return false;
}

//-----------------------------------------------------------------------------
// Name：DInputClass::IsMouseButtonDown()
// Desc: 判断鼠标上某键是否按下
//-----------------------------------------------------------------------------
bool S2D3DMouse::IsMouseButtonDown(int button)
{
    return (m_mouseState.rgbButtons[button] & 0x80) != 0;
}


//-----------------------------------------------------------------------------
// Name：DInputClass::MouseDX
// Desc: 返回鼠标指针的X轴坐标值
//-----------------------------------------------------------------------------
float S2D3DMouse::GetMouseDX()
{
    return (float)m_mouseState.lX;
}


//-----------------------------------------------------------------------------
// Name：DInputClass::MouseDY
// Desc: 返回鼠标指针的Y轴坐标值
//-----------------------------------------------------------------------------
float S2D3DMouse::GetMouseDY()
{
    return (float)m_mouseState.lY;
}

//-----------------------------------------------------------------------------
// Name：DInputClass::MouseDZ
// Desc: 返回鼠标指针的Z轴坐标值（滚轮）
//-----------------------------------------------------------------------------
float S2D3DMouse::GetMouseDZ()
{
    return (float)m_mouseState.lZ;
}

S2Vector3 S2D3DMouse::GetMouseDXYZ()
{
    return S2Vector3(GetMouseDX(), GetMouseDY(), GetMouseDZ());
}