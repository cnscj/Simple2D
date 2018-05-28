/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-08 22:08:47 
 * @Brief: 绘图类实现
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-08 22:10:27
 * @Last Modified log: 
 */
#include "S2Painter.h"
#include "S2Renderer.h"

#include "S2Font.h"
#include "S2Texture.h"

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

S2Painter::S2Painter(S2Renderer *pRenderer)
{
    m_pRenderer = pRenderer;
    m_pRenderer->Retain();
}
S2Painter::~S2Painter()
{
    S2SAFERELEASE(m_pRenderer);
}

S2Renderer *S2Painter::GetRenderer()const
{
    return m_pRenderer;
}



//绘制纹理
S2Result S2Painter::DrawImage(
    const S2Texture *pTexture,              //纹理指针
    const S2Point *pDestPos,                //目标位置
    const S2Size *pDestSize,                //目标大小
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

    int nDestPosX = pDestPos ? pDestPos->GetX() : 0;
    int nDestPosY = pDestPos ? pDestPos->GetY() : 0;
    int nDestWidth = pDestSize ? (pDestSize->GetWidth() >= 0 ? pDestSize->GetWidth() : nOriWidth) : nOriWidth;
    int nDestHeight = pDestSize ? (pDestSize->GetHeight() >= 0 ? pDestSize->GetHeight() : nOriHeight) : nOriHeight;

    int nSrcPosX = pSrcRt ? pSrcRt->GetX() : 0;
    int nSrcPosY = pSrcRt ? pSrcRt->GetY() : 0;
    int nSrcWidth = pSrcRt ? pSrcRt->GetWidth() : nOriWidth;
    int nSrcHeight = pSrcRt ? pSrcRt->GetHeight() : nOriHeight;


    D3DTLVERTEX v[4];
    memset(v, 0, sizeof(v));
    //顶点初始化
    {
        if (pMat)
        {
            //坐标与矩阵的变换  [x' y' z' 1] = [x y z 1] * pMat
            v[0].x = (float)(nDestPosX)* pMat->_11 + (float)(nDestPosY)* pMat->_21 + pMat->_41;
            v[0].y = (float)(nDestPosX)* pMat->_12 + (float)(nDestPosY)* pMat->_22 + pMat->_42;
            v[1].x = (float)(nDestPosX + nDestWidth)* pMat->_11 + (float)(nDestPosY)* pMat->_21 + pMat->_41;
            v[1].y = (float)(nDestPosX + nDestWidth)* pMat->_12 + (float)(nDestPosY)* pMat->_22 + pMat->_42;
            v[2].x = (float)(nDestPosX + nDestWidth)* pMat->_11 + (float)(nDestPosY + nDestHeight)* pMat->_21 + pMat->_41;
            v[2].y = (float)(nDestPosX + nDestWidth)* pMat->_12 + (float)(nDestPosY + nDestHeight)* pMat->_22 + pMat->_42;
            v[3].x = (float)(nDestPosX)* pMat->_11 + (float)(nDestPosY + nDestHeight)* pMat->_21 + pMat->_41;
            v[3].y = (float)(nDestPosX)* pMat->_12 + (float)(nDestPosY + nDestHeight)* pMat->_22 + pMat->_42;
        }
        else{
            //没有与矩阵运算的坐标
            v[0].x = v[3].x = (float)(nDestPosX);
            v[1].x = v[2].x = (float)(nDestPosX + nDestWidth);
            v[0].y = v[1].y = (float)(nDestPosY);
            v[2].y = v[3].y = (float)(nDestPosY + nDestHeight);
        }

        v[0].z = v[1].z = v[2].z = v[3].z = 1.0f;   //Z深度-应该大于0以免覆盖UI

        v[0].rhw = v[1].rhw = v[2].rhw = v[3].rhw = 1.0f;

        //纹理坐标等比缩放
        v[0].tu = (float)nSrcPosX / nOriWidth; v[0].tv = (float)nSrcPosY / nOriHeight;
        v[1].tu = (float)(nSrcPosX + nSrcWidth) / nOriWidth; v[1].tv = (float)nSrcPosY / nOriHeight;
        v[2].tu = (float)(nSrcPosX + nSrcWidth) / nOriWidth; v[2].tv = (float)(nSrcPosY + nSrcHeight) / nOriHeight;
        v[3].tu = (float)nSrcPosX / nOriWidth; v[3].tv = (float)(nSrcPosY + nSrcHeight) / nOriHeight;
    }
    //
    auto pd3dDevice = GetRenderer()->GetDeviceHandle<LPDIRECT3DDEVICE9>();

    pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
    pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);           //开启Alpha混合
    pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);      //设置源混合因子,混合因子之源Alpha  
    pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);  //设置目标混合因子,混合因子之源Alpha翻转,D3DBLEND_INVS

    //TODO:还是无法解决bmp,jpg透明问题
    pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

    pd3dDevice->SetTextureStageState(0, D3DTSS_CONSTANT, (DWORD)dwColor);
    pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CONSTANT);//如果没有alpha则从设置的值取

    pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

    pd3dDevice->SetTexture(0, pTexture->GetHandle<IDirect3DTexture9*>());
    pd3dDevice->SetFVF(D3DFVF_TLVERTEX);
    pd3dDevice->DrawPrimitiveUP((D3DPRIMITIVETYPE)D3DPT_TRIANGLEFAN, 2, (void *)v, sizeof(D3DTLVERTEX));

    return S_OK;
}

//绘制文本
S2Result S2Painter::DrawString(
    const S2Font *pFont,                    //字体指针
    const S2String &strWords,               //绘制的文字
    const S2Rect *pRect,                    //包围框大小
    S2ColorRef Color,                       //颜色
    S2uInt uFormat                          //格式
    )
{
    if (!pFont)
        return E_FAIL;

    auto pFontHandle = pFont->GetHandle<ID3DXFont *>();

    RECT rt;
    rt.left = pRect ? pRect->left : 0;
    rt.top = pRect ? pRect->top : 0;
    rt.right = pRect ? pRect->right : 0;
    rt.bottom = pRect ? pRect->bottom : 0;

    return pFontHandle->DrawText(NULL, strWords.c_str(), strWords.length(), (pRect ? &rt : nullptr), uFormat, (D3DCOLOR)Color);
}