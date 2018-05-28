#ifndef _S2DXGLOBAL_H_
#define _S2DXGLOBAL_H_

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#define S2DX_HR(x)                 { hr = x; if( FAILED(hr) ) { return hr; } }         //自定义一个HR宏，方便执行错误的返回

#endif