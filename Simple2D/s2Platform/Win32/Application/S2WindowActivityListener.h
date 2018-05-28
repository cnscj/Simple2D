/**
*	S2WindowActivityListener类
*	窗口活动监听类
*	@author ZeroX
*	@version v1.0 11/08/2017
*/

#ifndef _S2WINDOWACTIVITYLISTENER_H_
#define _S2WINDOWACTIVITYLISTENER_H_
#include <Windows.h>

class S2WindowActivityListener
{
  public:
	//控件创建之前
	virtual BOOL OnCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) { return TRUE; }

	//绘制绘制事件
	virtual void OnPaint(HDC hDc) {}

	//窗口空闲事件
	virtual void OnFrame() { ::Sleep(10); }

	//处理子控件
	virtual void OnCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {}

	//关闭窗口
	virtual BOOL OnClose(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) { return TRUE; }

	//销毁窗口
	virtual void OnDestory(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {}

	//窗口改变
	virtual void OnSizeChanged(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {}

	//取得窗口焦点
	virtual void OnGetFocus(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {}

	//失去焦点
	virtual void OnLostFocus(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {}

	//其他消息处理
	virtual LRESULT CALLBACK OnOtherProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		return ::DefWindowProc(hWnd, message, wParam, lParam);
	}
};

#endif