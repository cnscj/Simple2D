/**
*	S2WindowInputListener类
*	窗口输入类
*	@author ZeroX
*	@version v1.0 11/08/2017
*/

#ifndef _S2WINDOWINPUTLISTENER_H_
#define _S2WINDOWINPUTLISTENER_H_
#include <Windows.h>

class S2WindowInputListener
{
  public:
	//键盘按下
	virtual void OnKeyDown(HWND hWnd, WPARAM wParam) {}
	//键盘弹起
	virtual void OnKeyUp(HWND hWnd, WPARAM wParam) {}
	//鼠标左键按下
	virtual void OnMouseLButtonDown(HWND hWnd, int x, int y, WPARAM wParam) {}
	//鼠标左键弹起
	virtual void OnMouseLButtonUp(HWND hWnd, int x, int y, WPARAM wParam) {}
	//鼠标滚轮
	virtual void OnMouseWheel(HWND hWnd, WPARAM wParam) {}
	//鼠标左键双击
	virtual void OnMouseDoubleClick(HWND hWnd, int x, int y, WPARAM wParam) {}
	//鼠标右键按下
	virtual void OnMouseRButtonDown(HWND hWnd, int x, int y, WPARAM wParam) {}
	//鼠标右键按下
	virtual void OnMouseRButtonUp(HWND hWnd, int x, int y, WPARAM wParam) {}
	//鼠标移动
	virtual void OnMouseMove(HWND hWnd, int x, int y, WPARAM wParam) {}
};

#endif