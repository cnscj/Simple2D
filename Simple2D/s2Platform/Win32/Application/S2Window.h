/**
*	S2Window
*	@brief 一个基于Win API 简单的窗口类
*	@author ZEROX
*	@link -
*	@version v1.1
*	@date 22/07/2017
*	@update 31/08/2017
*/

#ifndef _S2WINDOW_H_
#define _S2WINDOW_H_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "S2WindowActivityListener.h"
#include "S2WindowInputListener.h"
//用于创建win的属性表
#ifndef _SWIDGET_H_
typedef struct tagWINATTRIBUTE
{
	LPCTSTR lpClassName;
	LPCTSTR lpWindowName;
	DWORD dwStyle;
	int nPosX;
	int nPosY;
	int nWidth;
	int nHeight;
	HWND hWndParent;
	HMENU hMenu;
	HINSTANCE hInstance;
	LPVOID lpParam;

	//附加项
	BOOL bEnabled;
	BOOL bVisible;

} WINATTRIBUTE, *LPWINATTRIBUTE;

#endif

class S2Window : public S2WindowActivityListener,
				 public S2WindowInputListener
{
	friend LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

  private:
	HWND m_hWnd;		   //窗口句柄
	HINSTANCE m_hinstance; //实例句柄
	ATOM m_wAtom;		   //类原子

	//临时属性表
	LPWNDCLASSEX m_lpWndClassEx;	 //类注册属性表
	LPWINATTRIBUTE m_lpWinAttribute; //窗口注册属性表
	//基本属性
	BOOL m_bFullScreen; //是否全屏

	//事件接口
	S2WindowActivityListener *m_pActivityListener;
	S2WindowInputListener *m_pInputListener;

  private:
	//初始化窗口
	void InitWindow();
	//关闭窗口
	void CloseWindow();
	//消息循环
	void RunWindow();
	//创建窗口
	BOOL PreCreateWindow(LPWNDCLASSEX, LPWINATTRIBUTE);
	BOOL(CreateWindow)
	();
	BOOL AftCreateWindow(HWND);

  protected:
	//消息函数
	virtual LRESULT CALLBACK OnProc(HWND, UINT, WPARAM, LPARAM);

	//创建前
	virtual BOOL OnPreCreate(LPWNDCLASSEX, LPWINATTRIBUTE);

	//创建后
	virtual BOOL OnAftCreate(HWND);

  public:
	//取窗口句柄
	HWND GetWnd();

	//取得窗口实例
	HINSTANCE GetInstance();

  public:
	// 获取设置控件可用状态
	BOOL IsEnabled();
	void SetEnabled(BOOL bEnabled);

	// 获取设置控件可见状态
	BOOL IsVisible();
	void SetVisible(BOOL bVisible);

	// 设置控件标题
	void SetTitle(LPTSTR szTitle);
	LPTSTR GetTitle(LPTSTR szTitle, int iCount);
	LPTSTR GetTitle();

	// 设置获取控件样式
	void AddStyle(DWORD dwStyle);
	void SetStyle(DWORD dwStyle);
	DWORD GetStyle();
	void ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);
	BOOL IsHaveStyle(DWORD dwStyle);

	// 获取设置控件位置
	POINT GetPos();
	int GetPosX();
	int GetPosY();
	void SetPos(int x, int y);
	void SetPosAtCenter(); //设置坐标为屏幕中心
	void MovePos(int x, int y);

	/* 以下要区分客户区与非客户区大小 */
	// 获取设置控件宽高
	int GetWidth();
	int GetHeight();
	void SetWidth(int nWidth);
	void SetHeight(int nHeight);
	SIZE GetSize();

	// 获取设置部件矩形
	RECT GetWindowRect();
	void MoveWindowRect(RECT rt, BOOL bReDraw = TRUE);
	void SetWindowRect(RECT rt, UINT uFlags, HWND hWndInsertAfter);
	void MoveWindowRect(int x, int y, int width, int height, BOOL bReDraw = TRUE);
	void SetWindowRect(int x, int y, int width, int height, UINT uFlags, HWND hWndInsertAfter);

	//取得部件客户区大小
	RECT GetWindowClientRect();
	void SetWindowClientRect(RECT rt, UINT uFlags, HWND hWndInsertAfter);
	void MoveWindowClientRect(RECT rt, BOOL bReDraw = TRUE);
	void SetWindowClientRect(int x, int y, int width, int height, UINT uFlags, HWND hWndInsertAfter);
	void MoveWindowClientRect(int x, int y, int width, int height, BOOL bReDraw = TRUE);

	/* 以下操作针对类-会影响父类的子类类型 */
	/* WndClass属性变更-只支持静态GCL_ */
	//替换菜单名
	void SetMenuName(LPTSTR lpMenuName);
	LPTSTR GetMenuName();
	//设置大图标
	void SetBigIcon(HICON szIcon);
	HICON GetBigIcon();
	//设置小图标
	void SetSmallIcon(HICON szIcon);
	HICON GetSmallIcon();
	//设置鼠标指针
	void SetCursorIcon(HCURSOR szIcon);
	HCURSOR GetCursorIcon();
	//替换背景画刷
	void SetBkBr(HBRUSH hBr);
	HBRUSH GetBkBr();
	//替换类风格
	void AddClassStyle(UINT style);
	void SetClassStyle(UINT style);
	UINT GetClassStyle();

  public:
	/* 设置全屏模式 */
	void SetFullScreen(BOOL bFullScreen);
	BOOL GetFullScreen();

	//设置获取事件接口
	void SetActivityListener(S2WindowActivityListener *pActivityListener);
	void SetInputListener(S2WindowInputListener *pInputListener);
	S2WindowActivityListener *GetActivityListener();
	S2WindowInputListener *GetInputListener();

  public:
	//显示窗口
	void ShowWindow();
	void ShowWindow(int nCmdShow);

	//隐藏控件
	void HideWindow();

	//更新控件
	void UpdateWindow();
	void UpdateWindow(int left, int top, int right, int bottom);

  public:
	void DoModal();

  protected:
	//空闲事件
	virtual void OnRunning();

  public:
	S2Window();
	virtual ~S2Window();
};

#endif
