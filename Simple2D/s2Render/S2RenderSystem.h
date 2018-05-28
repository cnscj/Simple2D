/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-28 13:57:47 
 * @Brief: 渲染系统
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-19 15:46:15
 * @Last Modified log: 
 */
#ifndef _S2RENDERSYSTEM_H_
#define _S2RENDERSYSTEM_H_
#include "../s2Core/S2Singleton.hpp"
#include "S2View.h"
class S2RenderSystem :public S2Singleton<S2RenderSystem>

{
public:
    S2RenderSystem();
    ~S2RenderSystem();
public:
    //初始化视图
    S2View *CreateViewWithHandle(void *hWnd);

    //创建View
    S2View *CreateViewWithSize(S2String strName, int nWidth, int nHeight);
};
#endif