#ifndef _APPDELEGATE_H_
#define _APPDELEGATE_H_
#include <s2Engine/S2Application.h>

class AppDelegate : public S2Application
{
    friend LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);
public:
    AppDelegate();
    ~AppDelegate();

protected:
    //完成启动时调用
    bool ApplicationFinishLaunching();

    //进入后台调用
    void ApplicationEnterBackground();

    //从后台恢复到前台调用
    void ApplicationEnterForeground();

private:
    //创建窗口
    bool        __CreateWindow();
    bool        __CreateDxView();
    bool        __SetInitConfig();
    void        __Run();
private:
    HWND        m_hWnd;                 //窗口句柄
    S2String    m_strTitle;             //窗口标题
    int         m_nWidth, m_nHeight;    //窗口大小
};



#endif