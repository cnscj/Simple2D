/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-03-07 11:34:08 
 * @Brief: 图形渲染器
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-08 12:09:06
 * @Last Modified log: 
 */

#ifndef _S2GRAPHICS_H_
#define _S2GRAPHICS_H_
#include "../s2Core/S2Object.h"

class S2Renderer;
class S2Texture;
class S2Font;

class S2Graphics : public S2Object
{
public:
    S2Graphics(S2Renderer *pRenderer);
    ~S2Graphics();

public:
    //设置世界变换
    S2Result SetWorldTransform(const S2Matrix *mat);
    S2Result GetWorldTransform(S2Matrix *mat)const;

    //设置投影变换
    S2Result SetProjTransform(const S2Matrix *mat);
    S2Result GetProjTransform(S2Matrix *mat)const;

    //设置视角变换
    S2Result SetViewTransform(const S2Matrix *mat);
    S2Result GetViewTransform(S2Matrix *mat)const;
public:
    /* 图像输出 */
    //绘制纹理
    S2Result DrawTexture(
        const S2Texture *pTexture,              //纹理指针
        const S2Rect *pDestRt,                  //目标矩形
        const S2Rect *pSrcRt,                   //源矩形
        const S2Matrix *pMat,                   //变换矩阵
        S2ColorRef dwColor,                     //关键色
        S2dWord dwRop                           //未知
    );

    S2Result DrawFont(
        const S2Font *pFont,                    //字体指针
        const S2String &strWords,               //绘制的文字
        const S2Rect *pRect,                    //包围框大小
        S2ColorRef Color,                       //颜色
        S2uInt uFormat                          //格式
    );

public:
    //取得渲染设备
    S2Renderer *GetRenderer()const;

    //取得渲染设备句柄
    template<class T = void*>
    T GetHandle() const
    {
        return static_cast<T>(m_pHandle);
    }
private:
    void               *m_pHandle;              //绘制器句柄
    S2Renderer         *m_pRenderer;            //渲染器
};
#endif