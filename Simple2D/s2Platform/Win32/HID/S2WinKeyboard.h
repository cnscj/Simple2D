#ifndef _S2WINKEYBOARD_H_
#define _S2WINKEYBOARD_H_
#include <Windows.h>
#include "../../../s2Protocol/S2HIDProtocol.h"
class S2WinKeyboard : public S2KeyboardProtocol
{
public:
    S2Function<void(S2Word)> OnKeyDown;
    S2Function<void(S2Word)> OnKeyUp;
    S2Function<void(S2Word)> OnKeyChar;
public:
    S2WinKeyboard();
    ~S2WinKeyboard();

public:
    S2WinKeyboard *CreateWithHandle(HWND hWnd,HINSTANCE hInstance);
public:
    //键盘按键是否被按下
    bool IsKeyDown(S2Word vKey);
    bool IsKeyClick(S2Word vKey);

private:
    static HHOOK sm_hhookKey;                          //拦截键盘消息的Hook
    static S2Set<S2WinKeyboard *> sm_keyListener;      //监听器列表
    static LRESULT CALLBACK __KeyBoardProc(INT nCode, WPARAM wParam, LPARAM lParam);

    HWND m_hWnd;        //窗口句柄
};

#endif