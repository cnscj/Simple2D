#include <windows.h>
#include "s2Scene/S2SceneSystem.h"
#include "s2Render/S2RenderSystem.h"
#include "AppDelegate.h"
#include "MainScene.hpp"
AppDelegate::AppDelegate()
:m_hWnd(NULL), m_strTitle("Application"), m_nWidth(800), m_nHeight(600)
{

}
AppDelegate::~AppDelegate()
{

}
//完成启动时调用
bool AppDelegate::ApplicationFinishLaunching()
{
    return true;
}

//进入后台调用
void AppDelegate::ApplicationEnterBackground()
{

}

//从后台恢复到前台调用
void AppDelegate::ApplicationEnterForeground()
{

}


//创建窗口
bool AppDelegate::__CreateWindow()
{
    HINSTANCE hInstance = ::GetModuleHandle(NULL);
    
    LPCSTR lpszClassName = m_strTitle.c_str();
    LPCSTR lpszTitle = lpszClassName;
    int nWidth = m_nWidth > 0 ? m_nWidth : 800;
    int nHeight = m_nHeight > 0 ? m_nHeight : 600;

    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = lpszClassName;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    if (!RegisterClassEx(&wcex))  //判断主窗口是否注册成功  
        return false;

    m_hWnd = ::CreateWindow(
        lpszClassName,
        lpszTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        nWidth,
        nHeight,
        NULL,
        NULL,
        hInstance, 
        NULL);

    if (!m_hWnd)
    {
        return false;
    }

    ShowWindow(m_hWnd, SW_SHOWNORMAL);
    UpdateWindow(m_hWnd);

    return true;

}

bool AppDelegate::__CreateDxView()
{
    S2View *pMainView = S2RenderSystem::GetInstance()->CreateViewWithHandle(m_hWnd);
    S2SceneSystem *pSceneSystem = S2SceneSystem::GetInstance();
    pSceneSystem->SetRenderView(pMainView);

    S2Scene *pScene = new MainScene();
    S2Director::GetInstance()->RunWithScene(pScene);
    return true;
}
bool AppDelegate::__SetInitConfig()
{


    return true;
}
void AppDelegate::Run()
{
    __CreateWindow();
    __CreateDxView();
    __SetInitConfig();
    __Run();

}
void AppDelegate::Shutdowm()
{
    PostQuitMessage(0);
}

void AppDelegate::__Run()
{
    MSG msg;
    // 初始化消息结构. 
    ZeroMemory(&msg, sizeof(MSG));

    // 循环进行消息处理
    while (true)
    {
        // 处理windows消息. 
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // 接收到WM_QUIT消息，退出程序. 
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            S2Director::GetInstance()->MainLoop();
        }
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    switch (message)
    {
    case WM_CREATE:
        AppDelegate::GetInstance()->ApplicationFinishLaunching();
        break;
  
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        // TODO: 在此添加任意绘图代码...  

       
        EndPaint(hWnd, &ps);
        break;
    case WM_SETFOCUS:                //游戏窗口得到焦点消息
        AppDelegate::GetInstance()->ApplicationEnterForeground();
        break;

    case WM_KILLFOCUS:                //游戏窗口失去焦点消息
        AppDelegate::GetInstance()->ApplicationEnterBackground();
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}