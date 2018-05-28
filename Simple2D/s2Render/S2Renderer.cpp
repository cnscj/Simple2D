#include "S2Renderer.h"
#include "S2View.h"
#include "S2Device.h"
#include "S2Shader.h"
#include "S2Effect.h"
#include "S2Painter.h"
#include "S2Graphics.h"

#include "S2Texture.h"
#include "S2Font.h"

#include "S2TexturePool.h"

#include "../s2Util/SXDXUtil.h"
S2Result S2Renderer::CreateWithView(S2View *pView)
{
    HWND hWnd = (HWND)pView->GetViewHandle();
    int nWidth = pView->GetViewWidth();
    int nHight = pView->GetViewHeight();
    bool isWindowed = pView->IsWindowed();

    //--------------------------------------------------------------------------------------
    // 【Direct3D初始化四步曲之一，创接口】：创建Direct3D接口对象, 以便用该Direct3D对象创建Direct3D设备对象
    //--------------------------------------------------------------------------------------
    LPDIRECT3D9  pD3D = NULL; //Direct3D接口对象的创建
    if (NULL == (pD3D = ::Direct3DCreate9(D3D_SDK_VERSION))) //初始化Direct3D接口对象，并进行DirectX版本协商
        return E_FAIL;

    //--------------------------------------------------------------------------------------
    // 【Direct3D初始化四步曲之二,取信息】：获取硬件设备信息
    //--------------------------------------------------------------------------------------
    D3DCAPS9 caps; int vp = 0;
    if (FAILED(pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
    {
        return E_FAIL;
    }
    if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
        vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;   //支持硬件顶点运算，我们就采用硬件顶点运算，妥妥的
    else
        vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING; //不支持硬件顶点运算，无奈只好采用软件顶点运算

    //--------------------------------------------------------------------------------------
    // 【Direct3D初始化四步曲之三，填内容】：填充D3DPRESENT_PARAMETERS结构体
    //--------------------------------------------------------------------------------------
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.BackBufferWidth = nWidth;
    d3dpp.BackBufferHeight = nHight;
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
    d3dpp.BackBufferCount = 1;
    d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
    d3dpp.MultiSampleQuality = 0;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = hWnd;
    d3dpp.Windowed = isWindowed;
    d3dpp.EnableAutoDepthStencil = true;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
    d3dpp.Flags = 0;
    d3dpp.FullScreen_RefreshRateInHz = 0;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    //--------------------------------------------------------------------------------------
    // 【Direct3D初始化四步曲之四，创设备】：创建Direct3D设备接口
    //--------------------------------------------------------------------------------------
    LPDIRECT3DDEVICE9 pd3dDevice = NULL; //Direct3D设备对象
    if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
        hWnd, vp, &d3dpp, &pd3dDevice)))
        return E_FAIL;

    // 设置渲染状态
    pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);          //关闭光照
    pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);    //开启背面消隐

    //LPDIRECT3D9接口对象的使命完成，我们将其释放掉
    S2SAFERELEASE(pD3D);

    ///////////////////////////////////
    m_pView = pView;
    m_pView->Retain();
    m_pDeviceHandle = (void *)pd3dDevice;
    m_pShader = new S2Shader(this);
    m_pDevice = new S2Device(this);

    return S_OK;
}

//设置世界变换矩阵
S2Result S2Renderer::SetTransform(TransformStateType type, const S2Matrix *mat)
{
    D3DXMATRIX d3mat;
    SXMatrixToDX9Matrix(mat, &d3mat);
    S2Result ret = ERROR_INVALID_PARAMETER;
    switch (type)
    {
    case TransformStateType::World:
    {
        ret = GetDeviceHandle<LPDIRECT3DDEVICE9>()->SetTransform(D3DTS_WORLD, &d3mat);
    }break;
    case TransformStateType::View:
    {
        ret = GetDeviceHandle<LPDIRECT3DDEVICE9>()->SetTransform(D3DTS_VIEW, &d3mat);
    }break;
    case TransformStateType::Proj:
    {
        ret = GetDeviceHandle<LPDIRECT3DDEVICE9>()->SetTransform(D3DTS_PROJECTION, &d3mat);
    }break;
    }
    return ret;
}
S2Result S2Renderer::GetTransform(TransformStateType type, S2Matrix *mat)const
{
    D3DXMATRIX d3mat;
    S2Result ret = ERROR_INVALID_PARAMETER;
    switch (type)
    {
    case TransformStateType::World:
    {
        ret = GetDeviceHandle<LPDIRECT3DDEVICE9>()->GetTransform(D3DTS_WORLD, &d3mat);
    }break;
    case TransformStateType::View:
    {
        ret = GetDeviceHandle<LPDIRECT3DDEVICE9>()->GetTransform(D3DTS_VIEW, &d3mat);
    }break;
    case TransformStateType::Proj:
    {
        ret = GetDeviceHandle<LPDIRECT3DDEVICE9>()->GetTransform(D3DTS_PROJECTION, &d3mat);
    }break;
    }
    DX9MatrixToSXMatrix(&d3mat,mat);
    return ret;
}

//根据文件创建纹理
S2Texture *S2Renderer::CreateTextureWithFile(S2String file)
{
    return S2TexturePool::GetInstance()->CreateWithFile(this,file);
    /*auto pTexture = S2Object::Create<S2Texture>();
    pTexture->CreateWithFile(this,file);
    return pTexture;*/
}
S2Texture *S2Renderer::CreateTextureWithResource(S2uInt unRcid)
{
    return S2TexturePool::GetInstance()->CreateWithResource(this, unRcid);
   /* auto pTexture = S2Object::Create<S2Texture>();
    pTexture->CreateWithResource(this, unRcid);
    return pTexture;*/
}
S2Texture *S2Renderer::CreateTextureWithMemory(const S2Data pAddr, S2uInt len)
{
    return S2TexturePool::GetInstance()->CreateWithMemory(this, pAddr, len);
    /*auto pTexture = S2Object::Create<S2Texture>();
    pTexture->CreateWithMemory(this, pAddr, len);
    return pTexture;*/
}

//根据格式创建字体
S2Font *S2Renderer::CreateFontWithFaceName(S2String strFacename, S2uInt height)
{
    auto pFont = S2Object::Create<S2Font>();
    pFont->CreateWithFaceName(this, strFacename, height);
    return pFont;
}
//////
S2Graphics *S2Renderer::CreateGraphics()
{
    if (!m_pGraphics)
    {
        m_pGraphics = S2Object::Create<S2Graphics>(this);
        m_pGraphics->Retain();
    }
   return m_pGraphics;
}
S2Painter *S2Renderer::CreatePainter()
{
    if (!m_pPainter)
    {
        m_pPainter = S2Object::Create<S2Painter>(this);
        m_pPainter->Retain();
    }
    return m_pPainter;

}
S2Effect *S2Renderer::CreateEffect()
{
    if (!m_pEffect)
    {
        m_pEffect = S2Object::Create<S2Effect>(this);
        m_pEffect->Retain();
    }
    return m_pEffect;

}

//取得渲染视图
S2View   *S2Renderer::GetView()const
{
    return m_pView;
}

//取得着色器
S2Shader *S2Renderer::GetShader()const
{
    return m_pShader;
}

//取得渲染设备
S2Device *S2Renderer::GetDevice()const
{
    return m_pDevice;
}

//开始渲染
S2Result S2Renderer::BeginRender()
{
    ++m_nRenderReqTimes;
    if(m_nRenderReqTimes>1) 
     return S_OK;
    //--------------------------------------------------------------------------------------
    // 【Direct3D渲染五步曲之一】：清屏操作
    //--------------------------------------------------------------------------------------
    GetDeviceHandle<LPDIRECT3DDEVICE9>()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    //--------------------------------------------------------------------------------------
    // 【Direct3D渲染五步曲之二】：开始绘制
    //--------------------------------------------------------------------------------------
    GetDeviceHandle<LPDIRECT3DDEVICE9>()->BeginScene();                     // 开始绘制

    return S_OK;
}

//结束渲染
S2Result S2Renderer::EndRender()
{
    --m_nRenderReqTimes;
    if(m_nRenderReqTimes>0) 
     return S_OK;
    //--------------------------------------------------------------------------------------
    // 【Direct3D渲染五步曲之四】：结束绘制
    //--------------------------------------------------------------------------------------
    GetDeviceHandle<LPDIRECT3DDEVICE9>()->EndScene();                       // 结束绘制
    //--------------------------------------------------------------------------------------
    // 【Direct3D渲染五步曲之五】：显示翻转
    //--------------------------------------------------------------------------------------
    GetDeviceHandle<LPDIRECT3DDEVICE9>()->Present(NULL, NULL, NULL, NULL);  // 翻转与显示
    
    return S_OK;
}

S2Renderer::S2Renderer()
:m_pDeviceHandle(nullptr), m_pView(nullptr), m_pShader(nullptr), m_pDevice(nullptr), m_nRenderReqTimes(0)
, m_pGraphics(nullptr), m_pPainter(nullptr), m_pEffect(nullptr)
{

}
S2Renderer::~S2Renderer()
{
    S2SAFERELEASE(m_pView);
    S2SAFERELEASE(m_pShader);
    S2SAFERELEASE(m_pDevice);
    S2RELEASE(GetDeviceHandle<LPDIRECT3DDEVICE9>());

    S2SAFERELEASE(m_pGraphics);
    S2SAFERELEASE(m_pPainter);
    S2SAFERELEASE(m_pEffect);
}