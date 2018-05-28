#include "S2Window.h"

//消息循环回调函数
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static S2Window *g_pAppWindow = NULL;
////
S2Window::S2Window()
{
	m_lpWndClassEx = new WNDCLASSEX();
	m_lpWinAttribute = new WINATTRIBUTE();

	g_pAppWindow = this;
	m_hWnd = NULL;
	m_hinstance = ::GetModuleHandle(NULL);

	m_pActivityListener = (S2WindowActivityListener *)this;
	m_pInputListener = (S2WindowInputListener *)this;

	InitWindow();
}
S2Window::~S2Window()
{
	if (g_pAppWindow)
		g_pAppWindow = NULL;
	delete m_lpWndClassEx;
	delete m_lpWinAttribute;
}
/////////
void S2Window::InitWindow()
{
	/* 设置属性表的默认值 */

	//WndClassEx初始化
	m_lpWndClassEx->lpszClassName = TEXT("s2window");			//设置窗口类名(提供给CreateWindow()使用)
	m_lpWndClassEx->style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; //垂直水平重绘,运行双击传递消息;(游戏窗口不建议采用CS_DBLCLKS样式)
	m_lpWndClassEx->hInstance = GetModuleHandle(NULL);			//指定义窗口应用程序的句柄
	m_lpWndClassEx->cbWndExtra = 0;								//指向窗口过程函数的指针. 可以使用 CallWindowProc函数调用窗口过程.
	m_lpWndClassEx->cbClsExtra = 0;								//指定紧跟在类之后的附加内存空间的字节数. 系统初始化为0.
	m_lpWndClassEx->lpfnWndProc = WndProc;						//默认选择自定义消息回调
	m_lpWndClassEx->hIconSm = LoadIcon(NULL, IDI_APPLICATION);  //加载程序图标（大）
	m_lpWndClassEx->hIcon = LoadIcon(NULL, IDI_APPLICATION);	//加载程序图标（小）
	m_lpWndClassEx->hCursor = LoadCursor(NULL, IDC_ARROW);		//加载鼠标样式
	m_lpWndClassEx->hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); //设置窗口背景色
	m_lpWndClassEx->lpszMenuName = NULL;						//设置窗口没有菜单
	m_lpWndClassEx->cbSize = sizeof(WNDCLASSEX);				//长度

	// WinAttribute初始化
	m_lpWinAttribute->lpClassName = m_lpWndClassEx->lpszClassName; //窗口类注册名
	m_lpWinAttribute->lpWindowName = TEXT("Window");			   //设置窗口标题-必须唯一
	m_lpWinAttribute->hInstance = m_lpWndClassEx->hInstance;	   //程序实例句柄
	m_lpWinAttribute->dwStyle = WS_OVERLAPPEDWINDOW;			   //定义窗口风格(系统菜单--默认只带一个关闭按钮)
	m_lpWinAttribute->hMenu = NULL;								   //菜单的句柄
	m_lpWinAttribute->hWndParent = NULL;						   //父窗口句柄
	m_lpWinAttribute->nPosX = CW_USEDEFAULT;					   //设置窗口左上角X坐标
	m_lpWinAttribute->nPosY = CW_USEDEFAULT;					   //设置窗口左上角Y坐标
	m_lpWinAttribute->nWidth = 800;								   //设置窗口宽度
	m_lpWinAttribute->nHeight = 600;							   //设置窗口高度
	m_lpWinAttribute->lpParam = NULL;							   //设置参数,让消息顺序能正确执行到对象消息,必须带上类型

	m_lpWinAttribute->bEnabled = TRUE;  //初始可用
	m_lpWinAttribute->bVisible = FALSE; //初始不可见

	m_bFullScreen = FALSE;

	SetPosAtCenter();
}

BOOL S2Window::PreCreateWindow(LPWNDCLASSEX lpWndClassEx, LPWINATTRIBUTE lpWinAttribute)
{
	if (!OnPreCreate(lpWndClassEx, lpWinAttribute))
		return FALSE;

	//样式附加操作
	if (!lpWinAttribute->bEnabled)
		lpWinAttribute->dwStyle |= WS_DISABLED;
	if (lpWinAttribute->bVisible)
		lpWinAttribute->dwStyle |= WS_VISIBLE;

	// 注册窗口类
	if (!RegisterClassEx(m_lpWndClassEx))
	{
		::MessageBox(NULL, TEXT("Class Register Error!"), TEXT("Error"), MB_OK);
		return FALSE;
	}
	return TRUE;
}

BOOL S2Window::AftCreateWindow(HWND hWnd)
{
	m_hWnd = hWnd;
	if (!m_hWnd)
	{
		::MessageBox(NULL, TEXT("Window Create Error!"), TEXT("Error"), MB_OK);
		return FALSE;
	}

	delete m_lpWndClassEx;
	delete m_lpWinAttribute;
	m_lpWndClassEx = NULL;
	m_lpWinAttribute = NULL;

	return OnAftCreate(hWnd);
}

//创建窗口
BOOL(S2Window::CreateWindow)
()
{
	BOOL bPreCreate = PreCreateWindow(m_lpWndClassEx, m_lpWinAttribute);

	HWND hWnd = ::CreateWindow(
		m_lpWinAttribute->lpClassName,  //窗口类注册名
		m_lpWinAttribute->lpWindowName, //设置窗口标题-必须唯一
		m_lpWinAttribute->dwStyle,		//设置窗口风格
		m_lpWinAttribute->nPosX,		//设置窗口左上角X坐标
		m_lpWinAttribute->nPosY,		//设置窗口左上角Y坐标
		m_lpWinAttribute->nWidth,		//设置窗口宽度
		m_lpWinAttribute->nHeight,		//设置窗口高度
		m_lpWinAttribute->hWndParent,   //父窗口句柄
		m_lpWinAttribute->hMenu,		//菜单的句柄
		m_lpWinAttribute->hInstance,	//程序实例句柄
		m_lpWinAttribute->lpParam);		//传递给消息函数的指针

	BOOL bAftCreate = AftCreateWindow(hWnd);

	return bPreCreate & bAftCreate;
}

void S2Window::RunWindow()
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
			OnRunning();
		}
	}
	return;
}

void S2Window::CloseWindow()
{
	//显示光标.
	//ShowCursor(true);
	// 恢复默认显示设置.
	if (m_bFullScreen)
	{
		ChangeDisplaySettings(NULL, 0);
	}
	//释放窗口句柄.
	DestroyWindow(m_hWnd);
	m_hWnd = NULL;
	// 释放应用程序实例.
	UnregisterClass((LPTSTR)m_wAtom, m_hinstance);
	//g_pAppWindow = NULL;
	return;
};

LRESULT CALLBACK S2Window::OnProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE: //窗口建立消息:CreateWindow函数请求创建窗口时发送此消息
		m_pActivityListener->OnCreate(hWnd, message, wParam, lParam);
		break;

	case WM_PAINT: //窗口重绘消息
	{
		//WARING:不写BeginPaint程序将会进入死循环,一直处理一个接一个的WM_PAINT消息
		PAINTSTRUCT ps; //定义，无初始化,由BeginPaint初始化
		HDC hDc = ::BeginPaint(m_hWnd, &ps);

		//负责窗口绘制工作,并且绘制其下子控件
		m_pActivityListener->OnPaint(hDc);

		::EndPaint(m_hWnd, &ps);
	}
	break;
	case WM_COMMAND:
		m_pActivityListener->OnCommand(hWnd, message, wParam, lParam);
		break;
	case WM_SIZE:
		m_pActivityListener->OnSizeChanged(hWnd, message, wParam, lParam);
		break;
	case WM_SETFOCUS: //游戏窗口得到焦点消息
		m_pActivityListener->OnGetFocus(hWnd, message, wParam, lParam);
		break;

	case WM_KILLFOCUS: //游戏窗口失去焦点消息
		m_pActivityListener->OnLostFocus(hWnd, message, wParam, lParam);
		break;

	case WM_CLOSE:														 //窗口关闭消息
		if (m_pActivityListener->OnClose(hWnd, message, wParam, lParam)) //窗口关闭前的处理
			::DestroyWindow(hWnd);										 //发出销毁窗口消息
		break;

	case WM_DESTROY: //程序销毁消息
		m_pActivityListener->OnDestory(hWnd, message, wParam, lParam);
		PostQuitMessage(0);
		break;
	////////////////////////////////
	case WM_KEYDOWN: //按键消息
		m_pInputListener->OnKeyDown(hWnd, wParam);
		break;
	case WM_KEYUP: //按键消息
		m_pInputListener->OnKeyUp(hWnd, wParam);
		break;

	case WM_LBUTTONDOWN: //鼠标左键按下消息
		m_pInputListener->OnMouseLButtonDown(hWnd, LOWORD(lParam), HIWORD(lParam), wParam);
		break;

	case WM_LBUTTONUP: //鼠标左键弹起消息
		m_pInputListener->OnMouseLButtonUp(hWnd, LOWORD(lParam), HIWORD(lParam), wParam);
		break;

	case WM_MOUSEWHEEL: //鼠标滚轮事件
		m_pInputListener->OnMouseWheel(hWnd, wParam);
		break;

	case WM_LBUTTONDBLCLK: //鼠标左键双击消息
		m_pInputListener->OnMouseDoubleClick(hWnd, LOWORD(lParam), HIWORD(lParam), wParam);
		break;

	case WM_RBUTTONDOWN: //鼠标右键按下消息
		m_pInputListener->OnMouseRButtonDown(hWnd, LOWORD(lParam), HIWORD(lParam), wParam);
		break;
	case WM_RBUTTONUP: //鼠标右键弹起消息
		m_pInputListener->OnMouseLButtonUp(hWnd, LOWORD(lParam), HIWORD(lParam), wParam);
		break;

	case WM_MOUSEMOVE: //鼠标移动消息
		m_pInputListener->OnMouseMove(hWnd, LOWORD(lParam), HIWORD(lParam), wParam);
		break;
	default:
		//调用函数处理
		return m_pActivityListener->OnOtherProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

//创建前
BOOL S2Window::OnPreCreate(LPWNDCLASSEX lpWndClassEx, LPWINATTRIBUTE lpWinAttribute)
{
	int &nPosX = lpWinAttribute->nPosX;
	int &nPosY = lpWinAttribute->nPosY;
	int &nWidth = lpWinAttribute->nWidth;
	int &nHeight = lpWinAttribute->nHeight;
	DWORD &dwStyle = lpWinAttribute->dwStyle;

	// 根据是否全屏设置不同的分辨率.
	if (m_bFullScreen)
	{
		DEVMODE dmScreenSettings; // 设备模式
		// 得到windows桌面分辨率
		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);
		//全屏模式下，设置窗口大小为windows桌面分辨率.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// 临时设置显示设备为全屏模式，注意：应用程序退出时候，将恢复系统默认设置。
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// 设置窗口的左上角坐标位置为(0,0). 样式为无边框
		nPosX = nPosY = 0;
		dwStyle = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP;
	}

	return TRUE;
}

//创建后
BOOL S2Window::OnAftCreate(HWND hWnd)
{
	// 显示窗口并设置其为焦点.
	::ShowWindow(hWnd, SW_SHOW);
	::SetForegroundWindow(hWnd);
	::SetFocus(hWnd);
	// 隐藏鼠标.
	//ShowCursor(false);

	return TRUE;
}
////////////////////////////////
HWND S2Window::GetWnd()
{
	return m_hWnd;
}
//取得窗口实例
HINSTANCE S2Window::GetInstance()
{
	return GetModuleHandle(NULL);
}
///////////////////////////////

BOOL S2Window::IsEnabled()
{
	if (m_hWnd)
	{
		BOOL ret = FALSE;
		DWORD tstyle = ::GetWindowLong(m_hWnd, GWL_STYLE);
		ret = ((tstyle & WS_DISABLED) != 0) ? TRUE : FALSE;
		return ret;
	}
	else
		return m_lpWinAttribute->bEnabled;
}
void S2Window::SetEnabled(BOOL bEnabled)
{
	if (m_hWnd)
		::EnableWindow(m_hWnd, bEnabled);
	else
		m_lpWinAttribute->bEnabled = bEnabled;
}

BOOL S2Window::IsVisible()
{
	if (m_hWnd)
		return ::IsWindowVisible(m_hWnd);
	else
		return m_lpWinAttribute->bVisible;
}
void S2Window::SetVisible(BOOL bVisible)
{
	if (m_hWnd)
	{
		if (bVisible)
			ShowWindow();
		else
			HideWindow();
	}
	else
		m_lpWinAttribute->bVisible = bVisible;
}
void S2Window::SetTitle(LPTSTR szTitle)
{
	if (m_hWnd)

		::SetWindowText(m_hWnd, szTitle);
	else
		m_lpWinAttribute->lpWindowName = szTitle;
}
LPTSTR S2Window::GetTitle()
{
	static TCHAR title[256];
	if (m_hWnd)
	{
		::GetWindowText(m_hWnd, title, 256);
		return title;
	}
	else
	{
		return (LPTSTR)m_lpWinAttribute->lpWindowName;
	}
}
LPTSTR S2Window::GetTitle(LPTSTR szTitle, int iCount)
{
	if (m_hWnd)
	{
		::GetWindowText(m_hWnd, szTitle, iCount);
		return szTitle;
	}
	else
		return (LPTSTR)m_lpWinAttribute->lpWindowName;
}

/* 设置控件样式 */
void S2Window::AddStyle(DWORD dwStyle)
{
	DWORD dOldstyle = GetStyle();
	SetStyle(dOldstyle | dwStyle);
}

void S2Window::SetStyle(DWORD dwStyle)
{
	if (m_hWnd)
	{
		::SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);
	}
	else
	{
		m_lpWinAttribute->dwStyle = dwStyle;
	}
}
DWORD S2Window::GetStyle()
{
	if (m_hWnd)
	{
		return ::GetWindowLong(m_hWnd, GWL_STYLE);
	}
	else
	{
		return m_lpWinAttribute->dwStyle;
	}
}

void S2Window::ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
{
	DWORD oldStyle = GetStyle();
	DWORD newStyle = oldStyle & ~dwRemove | dwAdd;
	SetStyle(newStyle);
	if (nFlags != 0)
	{
		RECT rt = GetWindowRect();
		SetWindowRect(rt, nFlags, 0);
	}
	UpdateWindow();
}

BOOL S2Window::IsHaveStyle(DWORD dwStyle)
{
	DWORD tstyle = 0;
	BOOL ret = FALSE;
	if (m_hWnd)
	{
		tstyle = ::GetWindowLong(m_hWnd, GWL_STYLE);
	}
	else
	{
		tstyle = m_lpWinAttribute->dwStyle;
	}
	ret = ((tstyle & dwStyle) != 0) ? TRUE : FALSE;
	return ret;
}

POINT S2Window::GetPos()
{
	POINT pt{0, 0};
	RECT rt = GetWindowRect();
	pt.x = rt.left;
	pt.y = rt.top;

	return pt;
}

int S2Window::GetPosX()
{
	return GetPos().x;
}
int S2Window::GetPosY()
{
	return GetPos().y;
}

void S2Window::SetPos(int x, int y)
{
	SetWindowRect(x, y, GetWidth(), GetHeight(), 0, NULL);
}

void S2Window::SetPosAtCenter()
{
	RECT rt = GetWindowRect();
	int nPosX = rt.left;
	int nPosY = rt.top;
	int nWidth = rt.right - rt.left;
	int nHeight = rt.bottom - rt.top;

	/*非全屏状态下，窗口显示在屏幕中心*/
	//计算加上边框后的窗口大小
	int tw = nWidth + ::GetSystemMetrics(SM_CXFIXEDFRAME) * 2;
	int th = nHeight + ::GetSystemMetrics(SM_CYFIXEDFRAME) * 10;

	//计算在窗口居中时，窗口左上角的位置
	nPosX = (::GetSystemMetrics(SM_CXSCREEN) - tw) / 2;
	nPosY = (::GetSystemMetrics(SM_CYSCREEN) - th) / 2;

	rt.left = nPosX;
	rt.top = nPosY;
	rt.right = nPosX + nWidth;
	rt.bottom = nPosY + nHeight;

	MoveWindowRect(rt);
}

void S2Window::MovePos(int x, int y)
{
	MoveWindowRect(x, y, GetWidth(), GetHeight());
}

int S2Window::GetWidth()
{
	RECT rt = GetWindowRect();
	return rt.right - rt.left;
}
int S2Window::GetHeight()
{
	RECT rt = GetWindowRect();
	return rt.bottom - rt.top;
}
void S2Window::SetWidth(int nWidth)
{
	MoveWindowRect(GetPosX(), GetPosY(), nWidth, GetHeight());
}
void S2Window::SetHeight(int nHeight)
{
	MoveWindowRect(GetPosX(), GetPosY(), GetWidth(), nHeight);
}

SIZE S2Window::GetSize()
{
	SIZE size = {0, 0};
	RECT rt = GetWindowRect();
	size.cx = rt.left + rt.right;
	size.cy = rt.top + rt.bottom;
	return size;
}

RECT S2Window::GetWindowRect()
{
	RECT rt;

	if (m_hWnd)
	{
		::GetWindowRect(m_hWnd, &rt);
	}
	else
	{
		rt.left = m_lpWinAttribute->nPosX;
		rt.top = m_lpWinAttribute->nPosY;
		rt.right = m_lpWinAttribute->nWidth + m_lpWinAttribute->nPosX;
		rt.bottom = m_lpWinAttribute->nHeight + m_lpWinAttribute->nPosY;
	}

	return rt;
}
void S2Window::MoveWindowRect(RECT rt, BOOL bReDraw)
{

	if (m_hWnd)
	{
		::MoveWindow(m_hWnd, rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top, bReDraw);
	}
	else
	{
		m_lpWinAttribute->nPosX = rt.left;
		m_lpWinAttribute->nPosY = rt.top;
		m_lpWinAttribute->nWidth = rt.right - rt.left;
		m_lpWinAttribute->nHeight = rt.bottom - rt.top;
	}
}

void S2Window::MoveWindowRect(int x, int y, int width, int height, BOOL bReDraw)
{
	RECT rt;
	rt.left = x;
	rt.top = y;
	rt.right = x + width;
	rt.bottom = y + height;
	MoveWindowRect(rt, bReDraw);
}

void S2Window::SetWindowRect(RECT rt, UINT uFlags, HWND hWndInsertAfter)
{
	if (m_hWnd)
	{
		::SetWindowPos(m_hWnd, hWndInsertAfter, rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top, uFlags);
	}
	else
	{
		m_lpWinAttribute->nPosX = rt.left;
		m_lpWinAttribute->nPosY = rt.top;
		m_lpWinAttribute->nWidth = rt.right - rt.left;
		m_lpWinAttribute->nHeight = rt.bottom - rt.top;
	}
}
void S2Window::SetWindowRect(int x, int y, int width, int height, UINT uFlags, HWND hWndInsertAfter)
{
	RECT rt;
	rt.left = x;
	rt.top = y;
	rt.right = x + width;
	rt.bottom = y + height;
	SetWindowRect(rt, uFlags, hWndInsertAfter);
}

RECT S2Window::GetWindowClientRect()
{
	RECT rt;

	if (m_hWnd)
	{
		::GetClientRect(m_hWnd, &rt);
	}
	else
	{
		rt.left = 0;
		rt.top = 0;
		/* TODo :未初始化前取得客户区大小不正确 */
		rt.right = m_lpWinAttribute->nWidth + m_lpWinAttribute->nPosX - 10;
		rt.bottom = m_lpWinAttribute->nHeight + m_lpWinAttribute->nPosY - 8;
	}

	return rt;
}

void S2Window::SetWindowClientRect(RECT rt, UINT uFlags, HWND hWndInsertAfter)
{
	RECT rtOri = GetWindowRect();
	RECT rtClient = GetWindowClientRect();

	int nNewX = rt.left - ((rtOri.right - rtOri.left) - (rtClient.right - rtClient.left)) / 2;
	int nNewY = rt.top - ((rtOri.bottom - rtOri.top) - (rtClient.bottom - rtClient.top)) / 2;
	int nNewWidth = (rtOri.right - rtOri.left) - (rtClient.right - rtClient.left) + (rt.right - rt.left);
	int nNewHeight = (rtOri.bottom - rtOri.top) - (rtClient.bottom - rtClient.top) + (rt.bottom - rt.top);

	SetWindowRect(nNewX, nNewY, nNewWidth, nNewHeight, uFlags, hWndInsertAfter);
}
void S2Window::SetWindowClientRect(int x, int y, int width, int height, UINT uFlags, HWND hWndInsertAfter)
{
	RECT rt;
	rt.left = x;
	rt.top = y;
	rt.right = x + width;
	rt.bottom = y + height;
	SetWindowClientRect(rt, uFlags, hWndInsertAfter);
}
void S2Window::MoveWindowClientRect(RECT rt, BOOL bReDraw)
{
	RECT rtOri = GetWindowRect();
	RECT rtClient = GetWindowClientRect();

	int nNewX = rt.left - ((rtOri.right - rtOri.left) - (rtClient.right - rtClient.left)) / 2;
	int nNewY = rt.top - ((rtOri.bottom - rtOri.top) - (rtClient.bottom - rtClient.top)) / 2;
	int nNewWidth = (rtOri.right - rtOri.left) - (rtClient.right - rtClient.left) + (rt.right - rt.left);
	int nNewHeight = (rtOri.bottom - rtOri.top) - (rtClient.bottom - rtClient.top) + (rt.bottom - rt.top);

	MoveWindowRect(nNewX, nNewY, nNewWidth, nNewHeight, bReDraw);
}

void S2Window::MoveWindowClientRect(int x, int y, int width, int height, BOOL bReDraw)
{
	RECT rt;
	rt.left = x;
	rt.top = y;
	rt.right = x + width;
	rt.bottom = y + height;
	MoveWindowClientRect(rt, bReDraw);
}

///////////////////
void S2Window::SetMenuName(LPTSTR lpMenuName)
{
	if (m_hWnd)
		::SetClassLong(m_hWnd, GCL_MENUNAME, (LONG)lpMenuName);
	else
		m_lpWndClassEx->lpszMenuName = lpMenuName;
}
LPTSTR S2Window::GetMenuName()
{
	if (m_hWnd)
		return (LPTSTR)::GetClassLong(m_hWnd, GCL_MENUNAME);
	else
		return (LPTSTR)m_lpWndClassEx->lpszMenuName;
}

void S2Window::SetCursorIcon(HCURSOR hIcon)
{

	if (m_hWnd)
	{
		long lCur = (long)hIcon;
		::SetClassLong(m_hWnd, GCL_HCURSOR, lCur);
	}
	else
		m_lpWndClassEx->hCursor = hIcon;
}
HCURSOR S2Window::GetCursorIcon()
{

	if (m_hWnd)
	{
		return (HCURSOR)::GetClassLong(m_hWnd, GCL_HCURSOR);
	}
	else
		return m_lpWndClassEx->hCursor;
}

void S2Window::SetBigIcon(HICON hIcon)
{
	if (m_hWnd)
	{
		long lCur = (long)hIcon;
		::SetClassLong(m_hWnd, GCL_HICON, lCur);
	}
	else
		m_lpWndClassEx->hIcon = hIcon;
}

HICON S2Window::GetBigIcon()
{
	if (m_hWnd)
	{
		return (HICON)::GetClassLong(m_hWnd, GCL_HICON);
	}
	else
		return m_lpWndClassEx->hIcon;
}

void S2Window::SetSmallIcon(HICON hIcon)
{
	if (m_hWnd)
	{
		long lCur = (long)hIcon;
		::SetClassLong(m_hWnd, GCL_HICONSM, lCur);
	}
	else
		m_lpWndClassEx->hIconSm = hIcon;
}

HICON S2Window::GetSmallIcon()
{
	if (m_hWnd)
	{
		return (HICON)::GetClassLong(m_hWnd, GCL_HICONSM);
	}
	else
		return m_lpWndClassEx->hIconSm;
}

//替换背景画刷
void S2Window::SetBkBr(HBRUSH hBr)
{
	if (m_hWnd)
	{
		::SetClassLong(m_hWnd, GCL_HBRBACKGROUND, (LONG)hBr);
	}
	else
		m_lpWndClassEx->hbrBackground = hBr;
}

HBRUSH S2Window::GetBkBr()
{
	if (m_hWnd)
	{
		return (HBRUSH)::GetClassLong(m_hWnd, GCL_HBRBACKGROUND);
	}
	else
		return m_lpWndClassEx->hbrBackground;
}

void S2Window::AddClassStyle(UINT style)
{
	UINT uOldStyle = GetClassStyle();
	SetClassStyle(uOldStyle | style);
}
void S2Window::SetClassStyle(UINT style)
{
	if (m_hWnd)
	{
		::SetClassLong(m_hWnd, GCL_STYLE, (LONG)style);
	}
	else
		m_lpWndClassEx->style = style;
}
UINT S2Window::GetClassStyle()
{
	if (m_hWnd)
	{
		return (UINT)::GetClassLong(m_hWnd, GCL_STYLE);
	}
	else
		return m_lpWndClassEx->style;
}
//////////////////////

/* 设置全屏模式 */
void S2Window::SetFullScreen(BOOL bFullScreen)
{
	m_bFullScreen = bFullScreen;
}
BOOL S2Window::GetFullScreen()
{
	return m_bFullScreen;
}

void S2Window::SetActivityListener(S2WindowActivityListener *pActivityListener)
{
	/* TODO:会造成内存泄漏?,但是自身不能delete */
	m_pActivityListener = pActivityListener;
}
void S2Window::SetInputListener(S2WindowInputListener *pInputListener)
{
	/* TODO:会造成内存泄漏?,但是自身不能delete */
	m_pInputListener = pInputListener;
}

S2WindowActivityListener *S2Window::GetActivityListener()
{
	return m_pActivityListener;
}
S2WindowInputListener *S2Window::GetInputListener()
{
	return m_pInputListener;
}

////////////
//显示控件
void S2Window::ShowWindow()
{
	ShowWindow(SW_SHOWNORMAL);
}
void S2Window::ShowWindow(int nCmdShow)
{
	::ShowWindow(m_hWnd, nCmdShow); //显示控件
}

//隐藏控件
void S2Window::HideWindow()
{
	ShowWindow(SW_HIDE);
}

//更新控件
void S2Window::UpdateWindow()
{

	::InvalidateRect(m_hWnd, NULL, FALSE); //更新区域添加一个矩形为整个窗体,不要擦掉背景
	::UpdateWindow(m_hWnd);				   //强制刷新窗口
}
//游戏用
void S2Window::UpdateWindow(int left, int top, int right, int bottom)
{
	RECT temp;
	temp.left = left;
	temp.top = top;
	temp.right = right;
	temp.bottom = bottom;
	::InvalidateRect(m_hWnd, &temp, FALSE); //更新区域添加一个矩形,不要擦掉背景
	::UpdateWindow(m_hWnd);					//强制刷新窗口,
}

//////////////////
void S2Window::DoModal()
{
	//创建窗口
	if (!(CreateWindow)())
		return;

	//消息循环
	RunWindow();
	//关闭窗口
	CloseWindow();
}
/////////////////////////////////

void S2Window::OnRunning()
{
	//渲染
	m_pActivityListener->OnFrame();
}

/////////////////////////////////
LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	return g_pAppWindow->OnProc(hwnd, umessage, wparam, lparam);
}