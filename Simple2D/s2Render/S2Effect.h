/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-08 09:13:54 
 * @Brief: 特效类
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-24 14:15:36
 * @Last Modified log: 
 */
#ifndef _S2EFFECT_H_
#define _S2EFFECT_H_
#include "../s2Core/S2Object.h"
class S2Renderer;
class S2Effect: public S2Object
{
public:
    S2Effect(S2Renderer *pRenderer);
    ~S2Effect();
public:
    //高斯模糊
    S2Result MakeGaussianBlur();
    //运动模糊
    S2Result MakeMotionBlur();
    //渐变
    S2Result MakeGradients();
    //变灰
    S2Result MakeGrey();
    //高光
    S2Result MakeHighlight();
    //正片叠底

    //滤色

    //老旧

    //中心


public:
    //镜面

    //对称

public:
    //取得渲染器
    S2Renderer *GetRenderer()const;
private:
    S2Renderer   *m_pRenderer;
};
#endif