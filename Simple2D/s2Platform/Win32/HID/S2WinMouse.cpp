#include "S2WinMouse.h"
S2WinMouse::S2WinMouse()
{
    
}
S2WinMouse::~S2WinMouse()
{
    if (sm_hhookMouseWheel && sm_hhookMouse)
    {
        sm_keyListener.erase(this);
        if (sm_keyListener.empty())
        {
            ::UnhookWindowsHookEx(sm_hhookMouseWheel);
            ::UnhookWindowsHookEx(sm_hhookMouse);
        }
    }

}

S2WinMouse *S2WinMouse::CreateWithHandle(HWND hWnd,HINSTANCE hInstance)
{
    if (!sm_hhookMouseWheel)
    {
        //最后一个参数为0,则为全局钩子
        sm_hhookMouseWheel = ::SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)S2WinMouse::__MouseWheelProc, hInstance, 0); 
    }
    if (!sm_hhookMouse)
    {
        sm_hhookMouse = ::SetWindowsHookEx(WH_MOUSE, (HOOKPROC)S2WinMouse::__MouseProc, hInstance, ::GetCurrentThreadId());
    }


    if (sm_hhookMouseWheel && sm_hhookMouse)
    {
        sm_keyListener.insert(this);
        m_hWnd = hWnd;
        return this;
    }
    return nullptr;
}


//鼠标按键是否被按下
bool S2WinMouse::IsMouseDown(MouseButtonDirection vButtom)
{
    if (vButtom == MouseButtonDirection::Left)
    {
        if (::GetAsyncKeyState(VK_LBUTTON) && 0x8000)
            return true;
    }
    else if (vButtom == MouseButtonDirection::Middle)
    {
        if (::GetAsyncKeyState(VK_MBUTTON) && 0x8000)
            return true;
    }
    else if (vButtom == MouseButtonDirection::Right)
    {
        if (::GetAsyncKeyState(VK_RBUTTON) && 0x8000)
            return true;
    }
    return false;
}

//获取鼠标水平垂直相对移动值
//FIXME:当鼠标不在移动时,Last仍为上一次的值,会产生错误
float S2WinMouse::GetMouseDX()
{
    return (float)(sm_mouseState.nX - sm_mouseLastState.nX);
}
float S2WinMouse::GetMouseDY()
{
    return (float)(sm_mouseState.nY - sm_mouseLastState.nY);
}

//获取鼠标滚轮相对移动值
float S2WinMouse::GetMouseDZ()
{
    return (float)(sm_mouseState.nZ - sm_mouseLastState.nZ);
}

S2Vector3 S2WinMouse::GetMouseDXYZ()
{
    return S2Vector3(GetMouseDX(), GetMouseDY(), GetMouseDZ());
}

LRESULT CALLBACK S2WinMouse::__MouseWheelProc(INT nCode, WPARAM wParam, LPARAM lParam)
{
    //记录上一次的位置,求出变化的值
    MSLLHOOKSTRUCT *pkbhs = (MSLLHOOKSTRUCT *)lParam;
    sm_mouseLastState = sm_mouseState;
    sm_mouseState.nX = pkbhs->pt.x;
    sm_mouseState.nY = pkbhs->pt.y;
    sm_mouseState.nZ = GET_WHEEL_DELTA_WPARAM(pkbhs->mouseData);
    
    switch (nCode)
    {
    case HC_ACTION:
    {
                      if (wParam == WM_MOUSEWHEEL) //鼠标滚轮事件
                      {
                          short value = GET_WHEEL_DELTA_WPARAM(pkbhs->mouseData);
                          for (auto &it : sm_keyListener)
                              it->OnMouseWheel(value);
                      }
    }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT CALLBACK S2WinMouse::__MouseProc(INT nCode, WPARAM wParam, LPARAM lParam)
{
    MOUSEHOOKSTRUCT *pkbhs = (MOUSEHOOKSTRUCT *)lParam;
    switch (nCode)
    {
    case HC_ACTION:
    {

                      switch (wParam)
                      {
                      case WM_LBUTTONDOWN: //鼠标左键按下消息
                          for (auto &it : sm_keyListener)
                              it->OnMouseLButtonDown();
                          break;

                      case WM_LBUTTONUP: //鼠标左键弹起消息
                          for (auto &it : sm_keyListener)
                              it->OnMouseLButtonUp();
                          break;

                      case WM_LBUTTONDBLCLK: //鼠标左键双击消息
                          for (auto &it : sm_keyListener)
                              it->OnMouseDoubleClick();
                          break;

                      case WM_RBUTTONDOWN: //鼠标右键按下消息
                          for (auto &it : sm_keyListener)
                              it->OnMouseRButtonDown();
                          break;

                      case WM_RBUTTONUP: //鼠标右键弹起消息
                          for (auto &it : sm_keyListener)
                              it->OnMouseRButtonUp();
                          break;

                      case WM_MOUSEMOVE: //鼠标移动消息
                          
                          for (auto &it : sm_keyListener)
                          {
                            if (it->m_hWnd)
                            {
                                RECT rt;
                                ::GetWindowRect(it->m_hWnd, &rt);
                                it->OnMouseMove(pkbhs->pt.x - rt.left, pkbhs->pt.y - rt.top);
                            }
                            else
                            {
                                it->OnMouseMove(pkbhs->pt.x, pkbhs->pt.y);
                            }
                          }
                          break;
                      }
    }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}