/**
*    S2View
*    @brief 渲染视图
*    @author cnscj
*    @link -
*    @version v1.0
*    @date 14/03/2018
*    @update 14/03/2018
*/

#ifndef _S2DXVIEW_H_
#define _S2DXVIEW_H_
#include "../s2Base/sPattern/SSingleton.hpp"
#include "../s2Core/S2Object.h"
#include "S2Renderer.h"

class S2View : public S2Object
{
    friend class S2Renderer;
public:
    S2View();
    virtual ~S2View();
public:
    //初始化视图
    virtual S2View *CreateWithHandle(void *phWnd);

    //创建View
    virtual S2View *CreateWithSize(S2String strName, int nWidth, int nHeight);
public:
    //取得视窗句柄
    template<class T = void*>
    T GetViewHandle()const
    {
        return static_cast<T>(m_pViewHandle);
    }
    //取得本View的渲染器
    S2Renderer *GetViewRenderer()const;
public:
    //取得视窗名称
    S2String GetViewName()const;

    S2uInt  GetViewWidth()const;

    S2uInt  GetViewHeight()const;

    S2Size  GetViewSize()const;

    //是否窗口化
    bool IsWindowed()const;

private:
    void        *m_pViewHandle;     //视窗句柄
    S2Renderer  *m_pRenderer;       //视图渲染器
};
#endif