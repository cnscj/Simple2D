#include "S2Graphics.h"
#include "S2Renderer.h"
#include "S2Texture.h"
#include "S2Font.h"

#include "../s2Util/SXDXUtil.h"
/* 2D顶点格式定义 */
//灵活顶点格式
//当顶点结构体中有D3DFVF_XYZRHW时，不再执行视图、投影、世界等变换和光线计算
const DWORD D3DFVF_TLVERTEX = (D3DFVF_XYZRHW | D3DFVF_TEX1);
typedef struct tagD3DTLVERTEX
{
    float x, y, z;
    float rhw;
    float tu, tv;
}D3DTLVERTEX;

////////////////////////////////
S2Graphics::S2Graphics(S2Renderer *pRenderer)
:m_pHandle(nullptr)
{
    m_pRenderer = pRenderer;
    m_pRenderer->Retain();

    auto pd3dDevice = GetRenderer()->GetDeviceHandle<LPDIRECT3DDEVICE9>();
    auto pSprite = (LPD3DXSPRITE)nullptr;
    if (::D3DXCreateSprite(pd3dDevice, &pSprite) == S_OK)
        m_pHandle = pSprite;

}
S2Graphics::~S2Graphics()
{
    S2SAFERELEASE(m_pRenderer);
    S2RELEASE(GetHandle<LPD3DXSPRITE>());
}

//设置世界变换
S2Result S2Graphics::SetWorldTransform(const S2Matrix *mat)
{
    return GetRenderer()->SetTransform(S2Renderer::TransformStateType::World, mat);
}
S2Result S2Graphics::GetWorldTransform(S2Matrix *mat)const
{
    return GetRenderer()->GetTransform(S2Renderer::TransformStateType::World, mat);
}

//设置投影变换
S2Result S2Graphics::SetProjTransform(const S2Matrix *mat)
{
    return GetRenderer()->SetTransform(S2Renderer::TransformStateType::Proj, mat);
}
S2Result S2Graphics::GetProjTransform(S2Matrix *mat)const
{
    return GetRenderer()->GetTransform(S2Renderer::TransformStateType::Proj, mat);
}

//设置视角变换
S2Result S2Graphics::SetViewTransform(const S2Matrix *mat)
{
    return GetRenderer()->SetTransform(S2Renderer::TransformStateType::View, mat);
}
S2Result S2Graphics::GetViewTransform(S2Matrix *mat)const
{
    return GetRenderer()->GetTransform(S2Renderer::TransformStateType::View, mat);
}

/////////////////////////////////
S2Result S2Graphics::DrawTexture(
    const S2Texture *pTexture,              //纹理指针
    const S2Rect *pDestRt,                  //目标矩形
    const S2Rect *pSrcRt,                   //源矩形
    const S2Matrix *pMat,                   //变换矩阵
    S2ColorRef dwColor,                     //关键色
    S2dWord dwRop                           //未知
    )
{
    if (!pTexture)
        return E_FAIL;

    int nOriWidth = pTexture->GetWidth();
    int nOriHeight = pTexture->GetHeight();
    int nSurfaceWidth = pTexture->GetSurfaceWidth();
    int nSurfaceHeight = pTexture->GetSurfaceHeight();

    int nDestPosX = pDestRt ? pDestRt->GetX() : 0;
    int nDestPosY = pDestRt ? pDestRt->GetY() : 0;
    //int nDestWidth = pDestRt ? pDestRt->GetWidth() : nOriWidth;
    //int nDestHeight = pDestRt ? pDestRt->GetHeight() : nOriHeight;

    int nSrcPosX = pSrcRt ? pSrcRt->GetX() : 0;
    int nSrcPosY = pSrcRt ? pSrcRt->GetY() : 0;
    int nSrcWidth = pSrcRt ? pSrcRt->GetWidth() : nOriWidth;
    int nSrcHeight = pSrcRt ? pSrcRt->GetHeight() : nOriHeight;

    auto scalrateW = (float)((float)nSurfaceWidth / (float)nOriWidth);
    auto scalrateH = (float)((float)nSurfaceHeight / (float)nOriHeight);

    auto pSprite = GetHandle<LPD3DXSPRITE>();
    D3DXMATRIX Mp;

    pSprite->Begin(D3DXSPRITE_ALPHABLEND);

    //渲染精灵
    //非2次幂纹理扩充按比例还原精灵帧矩形
    RECT srcRECT;
    srcRECT.left = (long)(nSrcPosX * scalrateW);
    srcRECT.top = (long)(nSrcPosY * scalrateH);
    srcRECT.right = srcRECT.left + (long)(nSrcWidth * scalrateW);
    srcRECT.bottom = srcRECT.top + (long)(nSrcHeight * scalrateH);

    //D3DXVECTOR3 descCenter;
    //descCenter.x =  0.f;
    //descCenter.y =  0.f;
    //descCenter.z = 0.f;

    D3DXVECTOR3 descPos;
    descPos.x = (float)nDestPosX;
    descPos.y = (float)nDestPosY;
    descPos.z = 1.f;

    //矩阵转换
    SXMatrixToDX9Matrix(pMat, &Mp);

    //只有纹理与实际比例不对时才进行精灵缩放
    if (scalrateW != 1.f || scalrateH != 1.f)
    {
        //XXX:非常大的开销,应该采用脏任务处理的方式
        //得到２Ｄ坐标转换矩阵
        D3DXMATRIX Mout;
        D3DXMATRIX Msc_1;
        D3DXMATRIX Ms;
        D3DXMATRIX Msc;

        //还原成非2次幂大小-绕某点缩放
        //以绘制点(左上角)为缩放点缩放,免得缩放后绘制点混乱(与坐标不一致)
        D3DXMatrixTranslation(&Msc, descPos.x, descPos.y, 0.f);
        D3DXMatrixInverse(&Msc_1, NULL, &Msc);
        D3DXMatrixScaling(&Ms, 1.f / scalrateW, 1.f / scalrateH, 1.f);
        D3DXMatrixMultiply(&Mout, &Msc_1, &Ms);
        D3DXMatrixMultiply(&Mout, &Mout, &Msc);

        D3DXMatrixMultiply(&Mp, &Mout, &Mp);
    }


    pSprite->SetTransform(&Mp);
    pSprite->Draw(pTexture->GetHandle<IDirect3DTexture9*>(), &srcRECT, NULL, &descPos, (DWORD)dwColor);

    pSprite->End();

    return S_OK;
}
S2Result S2Graphics::DrawFont(
    const S2Font *pFont,                    //字体指针
    const S2String &strWords,               //绘制的文字
    const S2Rect *pRect,                    //包围框大小
    S2ColorRef Color,                       //颜色
    S2uInt uFormat                          //格式
    )
{
    auto pFontHandle = pFont->GetHandle<ID3DXFont *>();
    RECT rt;
    rt.left = pRect ? pRect->left : 0;
    rt.top = pRect ? pRect->top : 0;
    rt.right = pRect ? pRect->right : 0;
    rt.bottom = pRect ? pRect->bottom : 0;

    return pFontHandle->DrawText(NULL, strWords.c_str(), strWords.length(), (pRect ? &rt : nullptr), uFormat, (D3DCOLOR)Color);

}

S2Renderer *S2Graphics::GetRenderer()const
{
    return m_pRenderer;
}