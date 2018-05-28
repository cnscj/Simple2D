/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-11 11:34:37 
 * @Brief: 图形绘制类
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-08 22:09:13
 * @Last Modified log: 
 */

#ifndef _S2PAINTER_H_
#define _S2PAINTER_H_
#include "../s2Core/S2Object.h"

class S2Renderer;
class S2Texture;
class S2Font;

class S2Painter : public S2Object
{
public:
    S2Painter(S2Renderer *pRenderer);
    ~S2Painter();
public:
    //设置画笔大小
    void SetPenSize();

    //设置画笔颜色
    void SetPenColor();
public:
    /* 基础绘图 */
    //绘制点
    S2Result DrawPoint(const S2Point &p);

    //绘制线
    S2Result DrawLine(const S2Point &p1, const S2Point &p2);

    //绘制矩形
    S2Result DrawRect(const S2Rect &rt);

    //绘制椭圆
    S2Result DrawEllipse(const S2Rect &rt);

    //绘制圆弧
    S2Result DrawArc(const S2Rect &rectangle, int startAngle, int spanAngle);

    //绘制饼图
    S2Result DrawPie(const S2Rect &rectangle, int startAngle, int spanAngle);

    //填充矩形
    S2Result FillRectangle(const S2Rect& Rect, const S2ColorRef* pColorArr);

    //填充圆
    S2Result FillCircle(const S2Rect& Center, float R, const S2Rect& CenterColor, const S2Rect& BoundColor, S2uInt Divide = 50);

    /* 图像输出 */
    //绘制纹理
    S2Result DrawImage(
        const S2Texture *pTexture,              //纹理指针
        const S2Point *pDestPos,                //目标位置
        const S2Size *pDestSize,                //目标大小
        const S2Rect *pSrcRt,                   //源矩形
        const S2Matrix *pMat,                   //变换矩阵
        S2ColorRef dwColor,                     //关键色
        S2dWord dwRop                           //未知
        );                         

    //绘制文本
    S2Result DrawString(
        const S2Font *pFont,                    //字体指针
        const S2String &strWords,               //绘制的文字
        const S2Rect *pRect,                    //包围框大小
        S2ColorRef Color,                       //颜色
        S2uInt uFormat                          //格式
        );                       

public:
    //取得渲染器
    S2Renderer *GetRenderer()const;

private:
    S2Renderer         *m_pRenderer;            //渲染器
};

#endif