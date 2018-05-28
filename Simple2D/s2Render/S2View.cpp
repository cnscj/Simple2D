#include "S2View.h"

S2View::S2View()
:m_pViewHandle(nullptr), m_pRenderer(nullptr)
{

}
S2View::~S2View()
{
    S2SAFERELEASE(m_pRenderer);
}
//初始化视图
S2View *S2View::CreateWithHandle(void *phWnd)
{
    m_pViewHandle = (void *)phWnd;

    //创建渲染器
    S2Renderer  *pRenderer = new S2Renderer();
    if (S_OK == pRenderer->CreateWithView(this))
    {
        m_pRenderer = pRenderer;

        D3DVIEWPORT9 vp;        //实例化一个D3DVIEWPORT9结构体，然后做填空题给各个参数赋值就可以了
        vp.X = 0;		        //表示视口相对于窗口的X坐标
        vp.Y = 0;		        //视口相对对窗口的Y坐标
        vp.Width = GetViewWidth();	    //视口的宽度
        vp.Height = GetViewHeight();    //视口的高度
        vp.MinZ = 0.0f;         //视口在深度缓存中的最小深度值
        vp.MaxZ = 1.0f;	        //视口在深度缓存中的最大深度值
        m_pRenderer->GetDeviceHandle<LPDIRECT3DDEVICE9>()->SetViewport(&vp); //视口的设置

        return this;
    }
    else{
        m_pViewHandle = nullptr;
        S2SAFERELEASE(pRenderer);
    }

    return nullptr;
}

//创建View
S2View *S2View::CreateWithSize(S2String strName, int nWidth, int nHeight)
{
    //TODO:依据名字创建,...这里是留给openGl用
    return nullptr;
}

//取得本View的渲染器
S2Renderer *S2View::GetViewRenderer()const
{
    return m_pRenderer;
}

//取得视窗名称
S2String S2View::GetViewName()const
{
    if (GetViewHandle<HWND>())
    {
        char szTitle[256];
        ::GetWindowText(GetViewHandle<HWND>(), szTitle, 256);
        return szTitle;
    }
    else
        return "";
}

S2uInt S2View::GetViewWidth()const
{
    if (GetViewHandle<HWND>())
    {
        RECT rt;
        ::GetWindowRect(GetViewHandle<HWND>(), &rt);
        return rt.right - rt.left;
    }
    return 0;
}

S2uInt S2View::GetViewHeight()const
{
    if (GetViewHandle<HWND>())
    {
        RECT rt;
        ::GetWindowRect(GetViewHandle<HWND>(), &rt);
        return rt.bottom - rt.top;
    }
    return 0;
}

S2Size  S2View::GetViewSize()const
{
    return S2Size(GetViewWidth(), GetViewHeight());
}

//是否窗口化
bool S2View::IsWindowed()const
{
    RECT rcApp, rcDesk;
    HWND ApphWnd = GetViewHandle<HWND>();
    HWND deskhWnd = ::GetDesktopWindow();
    HWND shellhWnd = ::GetShellWindow();

    ::GetWindowRect(deskhWnd, &rcDesk);
    ::GetWindowRect(ApphWnd, &rcApp);

    if (ApphWnd != deskhWnd && ApphWnd != shellhWnd)
    {
        if (rcApp.left <= rcDesk.left
            && rcApp.top <= rcDesk.top
            && rcApp.right >= rcDesk.right
            && rcApp.bottom >= rcDesk.bottom)
        {
            return false;
        }
    }
    return true;
}