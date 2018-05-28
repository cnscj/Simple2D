#include "S2WinKeyboard.h"
S2WinKeyboard::S2WinKeyboard()
{
    
}
S2WinKeyboard::~S2WinKeyboard()
{
    if (sm_hhookKey)
    {
        sm_keyListener.erase(this);
    }

    if (sm_keyListener.empty())
    {
        ::UnhookWindowsHookEx(sm_hhookKey);
    }
}

S2WinKeyboard *S2WinKeyboard::CreateWithHandle(HWND hWnd, HINSTANCE hInstance)
{
    if (!sm_hhookKey)
    {
        //最后一个参数为0,则为全局钩子 
        sm_hhookKey = ::SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)S2WinKeyboard::__KeyBoardProc, hInstance, ::GetCurrentThreadId()); 
    }

    if (sm_hhookKey)
    {
        sm_keyListener.insert(this);
        m_hWnd = hWnd;
        return this;
    }
    return nullptr;
}

//键盘按键是否被按下
bool S2WinKeyboard::IsKeyDown(S2Word vKey)
{
    if (::GetAsyncKeyState(vKey) && 0x8000)
        return true;
    else
        return false;
}

bool S2WinKeyboard::IsKeyClick(S2Word vKey)
{
    //按下弹起为一次
    if (::GetKeyState(vKey) < 0)
        return true;
    else
        return false;
}


LRESULT CALLBACK S2WinKeyboard::__KeyBoardProc(INT nCode, WPARAM wParam, LPARAM lParam)
{

    switch (nCode)
    {
    case HC_ACTION:
    {
                      //lParam第30位代表之前按键是否按下(1)或释放(0),第31位表示正在被按下(0)或正在释放(1)
                      //	DWORD nHavePress = ((lParam >> 30) & 0x01);
                      //按键翻译
                      DWORD msg = 0x00;
                      {
                          if ((lParam >> 30) & 0x01)
                          { //表示按键之前有没有被按下
                              if ((lParam >> 31) & 0x01)
                                  msg = WM_KEYUP;
                          }
                          else
                          {
                              msg = WM_KEYDOWN;
                          }
                      }

                      switch (msg)
                      {
                      case WM_KEYDOWN: //按键消息 - 按下
                          for (auto &it : sm_keyListener)
                              it->OnKeyDown(wParam);
                          break;
                      case WM_KEYUP: //按键消息  - 释放
                          for (auto &it : sm_keyListener)
                              it->OnKeyUp(wParam);
                          break;
                      }
                      //直接回传
                      for (auto &it : sm_keyListener)
                          it->OnKeyChar(wParam);
    }
    default:
        break;
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}