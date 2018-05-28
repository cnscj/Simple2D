
#ifndef _S2WINMOUSE_H_
#define _S2WINMOUSE_H_
#include <Windows.h>
#include "../../../s2Protocol/S2HIDProtocol.h"

typedef struct tagS2WINMOUSE_STATE
{
    int nX = 0, nY = 0;
    int nZ = 0;
}S2WINMOUSE_STATE;

class S2WinMouse : public S2MouseProtocol
{
public:
    S2Function<void()> OnMouseLButtonDown;
    S2Function<void()> OnMouseLButtonUp;
    S2Function<void(int)> OnMouseWheel;
    S2Function<void()> OnMouseDoubleClick;
    S2Function<void()> OnMouseRButtonDown;
    S2Function<void()> OnMouseRButtonUp;
    S2Function<void(int, int)> OnMouseMove;
public:
    S2WinMouse();
    ~S2WinMouse();
public:
    S2WinMouse *CreateWithHandle(HWND hWnd,HINSTANCE hInstance);
public:

    //鼠标按键是否被按下
    bool IsMouseDown(MouseButtonDirection vButtom);

    //获取鼠标水平垂直滚轮相对移动值
    S2Vector3 GetMouseDXYZ();
    float GetMouseDX();
    float GetMouseDY();
    float GetMouseDZ();


private:
    static S2WINMOUSE_STATE sm_mouseState;			//记录值
    static S2WINMOUSE_STATE sm_mouseLastState;      //上一次记录
    static HHOOK sm_hhookMouseWheel;		        //鼠标全局钩子句柄
    static HHOOK sm_hhookMouse;			            //拦截鼠标消息的Hook
    static S2Set<S2WinMouse *> sm_keyListener;      //监听器列表
    static LRESULT CALLBACK __MouseWheelProc(INT nCode, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK __MouseProc(INT nCode, WPARAM wParam, LPARAM lParam);

    HWND m_hWnd;        //窗口句柄
};
#endif