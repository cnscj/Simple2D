#ifndef _SMATHX_H_
#define _SMATHX_H_

#include "SMath.h"
#include "SBasePoint3.hpp"
#include "SBaseVector2.hpp"
#include "SBaseVector3.hpp"
#include "SBaseVector4.hpp"
#include "SBaseQuaternion.hpp"
#include "SBaseMatrix.hpp"
#include "SBasePoint2.hpp"
#include "SBaseSize.hpp"
#include "SBaseRect.hpp"
#include "SBaseRgn.hpp"

namespace SMathX
{
    ///
    template <class T>
    T GetDistance(const SBasePoint2<T> &a, const SBasePoint2<T> &b);

    template <class T>
    SBaseVector2<T> GetVector(const SBasePoint2<T> &s, const SBasePoint2<T> &e);

    ///
    template <class T>
    T GetLength(const SBaseVector2<T> &v);

    template <class T>
    T GetDot(const SBaseVector2<T> &v1, const SBaseVector2<T> &v2);

    template <class T>
    T GetCrossValue(const SBaseVector2<T> &v1, const SBaseVector2<T> &v2);

    template <class T>
    SBaseVector3<T> GetCross(const SBaseVector2<T> &v1, const SBaseVector2<T> &v2);

    template <class T>
    T GetAngle(const SBaseVector2<T> &v1, const SBaseVector2<T> &v2);

    ///
    //碰撞函数
    template <class T>
    bool IsCollsion(const SBasePoint2<T> &pt1,const SBasePoint2<T> &pt2);
    template <class T>
    bool IsCollsion(const SBasePoint2<T> &pt, const SBaseRect<T> &rt);
    template <class T>
    bool IsCollsion(const SBaseRect<T> &rt1, const SBaseRect<T> &rt2);

    //是否在矩形内
    template <class T>
    bool IsInRect(const SBasePoint2<T> &pt, const SBaseRect<T> &rt);
    template <class T>
    bool IsInRect(const SBaseRect<T> &rt1, const SBaseRect<T> &rt2);

    //在矩形上
    template <class T>
    bool IsOnRect(const SBasePoint2<T> &pt, const SBaseRect<T> &rt);


    ///////////////////////////////////
    template <class T>
    T GetDistance(const SBasePoint3<T> &a, const SBasePoint3<T> &b);

    template <class T>
    SBaseVector3<T> GetVector(const SBasePoint3<T> &s, const SBasePoint3<T> &e);

    //
    template <class T>
    T GetLength(const SBaseVector3<T> &v);

    template <class T>
    T GetDot(const SBaseVector3<T> &v1, const SBaseVector2<T> &v2);

    template <class T>
    SBaseVector3<T> GetCross(const SBaseVector3<T> &v1, const SBaseVector3<T> &v2);

    template <class T>
    T GetAngle(const SBaseVector3<T> &v1, const SBaseVector3<T> &v2);

};

////////////////////////////////////////////////
///				以下是2纬点操作			     ///
////////////////////////////////////////////////

template <class T>
double SPoint2Distance(const SBasePoint2<T> *a, const SBasePoint2<T> *b);


////////////////////////////////////////////////
///				以下是2纬向量操作			 ///
////////////////////////////////////////////////

template <class T>
double SVec2Length(const SBaseVector2<T> *v);

template <class T>
T SVec2Dot(const SBaseVector2<T> *v1, const SBaseVector2<T> *v2);

template <class T>
T SVec2CrossValue(const SBaseVector2<T> *v1, const SBaseVector2<T> *v2);

template <class T>
SBaseVector3<T> SVec2Cross(const SBaseVector2<T> *v1, const SBaseVector2<T> *v2);

template <class T>
double SVec2Angle(const SBaseVector2<T> *v1, const SBaseVector2<T> *v2);

template <class T>
void SVec2Normalize(SBaseVector2<T> *v);

////////////////////////////////////////////////
///				以下是2纬矩形操作			 ///
////////////////////////////////////////////////

//求两个矩形的碰撞交集
template <class T>
bool SRectIntersect(const SBaseRect<T> *pSrcRt1, const SBaseRect<T> *pSrcRt2, SBaseRect<T> *pDstRt);

////////////////////////////////////////////////
///				以下是2维矩阵操作			 ///
////////////////////////////////////////////////
//创建2D的变换矩阵，就是在XY平面内变换矩阵。如果参数为NULL就当作单位矩阵看待。
template <class T>
SBaseMatrix<T> *SMatrixTransformation2D(
    SBaseMatrix<T>			*pOut,						//要输出结构的变换矩阵
    const SBaseVector2<T>	*pScalingCenter,			//缩放中心向量。如果参数为NULL，Msc 矩阵为单位矩阵。
    float					pScalingRotation,			//指向缩放旋转系数。
    const SBaseVector2<T>	*pScaling,					//结构的缩放向量。如果参数为NULL，Ms矩阵为单位矩阵。
    const SBaseVector2<T>	*pRotationCenter,			//结构的旋转向量。如果参数为NULL，Mrc矩阵为单位矩阵。
    float					Rotation,					//旋转角度。
    const SBaseVector2<T>	*pTranslation				//结构的平移向量。如果参数为NULL，Mt矩阵为单位矩阵。
    );

//创建一个仿射变换变换矩阵。NULL的参数就会当作是单位矩阵。
template <class T>
SBaseMatrix<T> *SMatrixAffineTransformation2D(
    SBaseMatrix<T>			*pOut,
    float                   Scaling,
    const SBaseVector2<T>   *pRotationCenter,
    float                   Rotation,
    const SBaseVector2<T>   *pTranslation
    );

//2D向量扩展到4D，Z=0,W用1填充。然后与矩阵相乘
template <class T>
SBaseVector2<T> *SVec2TransformCoord(SBaseVector2<T> *pOut, const SBaseVector2<T> *pV, const SBaseMatrix<T> *pM);

//2D向量扩展到4D，Z=0,W用0填充。然后与矩阵相乘
template <class T>
SBaseVector2<T> *SVec3TransformNormal(SBaseVector2<T> *pOut, const SBaseVector2<T> *pV, const SBaseMatrix<T> *pM);


////////////////////////////////////////////////
///				以下是3纬点操作			     ///
////////////////////////////////////////////////


template <class T>
double SPoint3Distance(const SBasePoint3<T> *a, const SBasePoint3<T> *b);


////////////////////////////////////////////////
///				以下是3维向量操作			 ///
////////////////////////////////////////////////

//向量叉乘
template <class T>
void SVec3Cross(SBaseVector3<T> *pOut, const SBaseVector3<T> *pV1, const SBaseVector3<T> *pV2);

//向量规范化
template <class T>
void SVec3Normalize(SBaseVector3<T> *pOut, const SBaseVector3<T> *pV);

//向量点乘
template <class T>
double SVec3Dot(const SBaseVector3<T> *pV1, const SBaseVector3<T> *pV2);

//向量长度
template <class T>
double SVec3Length(const SBaseVector3<T> *pV);

//取得向量夹角(弧度)
template <class T>
double SVec3Angle(const SBaseVector3<T> *pV1, const SBaseVector3<T> *pV2);
////////////////////////////////////////////////
///				以下是3维矩阵操作			 ///
////////////////////////////////////////////////
//两个矩阵相乘
template <class T>
SBaseMatrix<T>* SMatrixMultiply(SBaseMatrix<T> *pOut, const SBaseMatrix<T> *pM1, const SBaseMatrix<T> *pM2);

/* 以下变化全部基于左手定则 */
//绕任意向量旋转的矩阵
template <class T>
SBaseMatrix<T>* SMatrixRotationAxis(SBaseMatrix<T> *pOut, const SBaseVector3<T> *pV, T Angle);

//绕任意向量端点旋转的矩阵
template <class T>
SBaseMatrix<T>* SMatrixRotationLine(SBaseMatrix<T> *pOut, SBaseVector3<T> *pV1, SBaseVector3<T> *pV2, T Angle);

//3D向量扩展到4D，W用1填充。然后与矩阵相乘
template <class T>
SBaseVector3<T> *SVec3TransformCoord(SBaseVector3<T> *pOut, const SBaseVector3<T> *pV, const SBaseMatrix<T> *pM);

//3D向量扩展到4D，W用0填充。然后与矩阵相乘
template <class T>
SBaseVector3<T> *SVec3TransformNormal(SBaseVector3<T> *pOut, const SBaseVector3<T> *pV, const SBaseMatrix<T> *pM);

//获得指定参数的透视投影矩阵，用于3D投影变换。
template <class T>
SBaseMatrix<T>* SMatrixPerspectiveFovLH(SBaseMatrix<T> *pOut, T fovy, T Aspect, T zn, T zf);

//用于视图坐标到投影坐标系的2D转换。
template <class T>
SBaseMatrix<T>* SMatrixOrthoLH(SBaseMatrix<T> *pOut, T w, T h, T zn, T zf);

//获得指定参数的透视投影矩阵，用于3D投影变换。
template <class T>
SBaseMatrix<T> * SMatrixPerspectiveOffCenterLH(SBaseMatrix<T> * pOut, T l, T r, T b, T t, T zn, T zf);

//生成绕X轴旋转的矩阵
template <class T>
SBaseMatrix<T>* SMatrixRotationX(SBaseMatrix<T> *pOut, T Angle);

//生成绕Y轴旋转的矩阵
template <class T>
SBaseMatrix<T>* SMatrixRotationY(SBaseMatrix<T> *pOut, T Angle);

//生成绕Z轴旋转的矩阵
template <class T>
SBaseMatrix<T>* SMatrixRotationZ(SBaseMatrix<T> *pOut, T Angle);

//创建一个单位矩阵
template <class T>
SBaseMatrix<T>* SMatrixIdentity(SBaseMatrix<T> *pOut);

//TODO:算法重写
//计算矩阵的逆矩阵()T
template <class T>
SBaseMatrix<T>* SMatrixInverse(SBaseMatrix<T> *pOut, T *pDeterminant, const SBaseMatrix<T> *pM);

//计算矩阵的转置矩阵()-1
template <class T>
SBaseMatrix<T>* SMatrixTranspose(SBaseMatrix<T> *pOut, const SBaseMatrix<T> *pM);

//创建一个沿着X,Y和Z轴方向缩放矩阵
template <class T>
SBaseMatrix<T>* SMatrixScaling(SBaseMatrix<T> *pOut, T sx, T sy, T sz);

//创建一个沿着X,Y和Z轴方向平移矩阵
template <class T>
SBaseMatrix<T>* SMatrixTranslation(SBaseMatrix<T> *pOut, T x, T y, T z);

//创建一个变换矩阵。如果参数设置为NULL，就当作单位矩阵处理。
template <class T>
SBaseMatrix<T> *SMatrixTransformation(
    SBaseMatrix<T>				*pOut,
    const SBaseVector3<T>		*pScalingCenter,	//结构的缩放中心向量。如果参数为NULL，Msc 矩阵为单位矩阵。
    const SBaseQuaternion<T>	*pScalingRotation,	//指向缩放旋转系数。
    const SBaseVector3<T>		*pScaling,			//缩放向量。如果参数为NULL，Ms矩阵为单位矩阵。
    const SBaseVector3<T>		*pRotationCenter,	//旋转向量。如果参数为NULL，Mrc矩阵为单位矩阵。
    const SBaseQuaternion<T>	pRotation,			//旋转角度。
    const SBaseVector3<T>		*pTranslation		//平移向量。如果参数为NULL，Mt矩阵为单位矩阵。
    );

//创建一个仿射变换变换矩阵。NULL的参数就会当作是单位矩阵。
template <class T>
SBaseMatrix<T> *SMatrixAffineTransformation(
    SBaseMatrix<T>				*pOut,				//返回结果的矩阵。	
    float						Scaling,			//缩放系数。
    const SBaseVector3<T>		*pRotationCenter,	//旋转中心向量。如果设置为NULL，就用一个单位矩阵代替Mrc 。
    const SBaseQuaternion<T>	*pRotation,			//旋转矩阵。如果参数为NULL，就用单位矩阵Mr 代替。
    const SBaseVector3<T>		*pTranslation		//变换向量。如果为NULL，就用单位矩阵Mt 。
    );
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template <class T>
T SMathX::GetDistance(const SBasePoint2<T> &a, const SBasePoint2<T> &b)
{
    return SPoint2Distance(&a, &b);
}

template <class T>
SBaseVector2<T> SMathX::GetVector(const SBasePoint2<T> &s, const SBasePoint2<T> &e)
{
    return SBaseVector2<T>(e.x - s.x, e.y - s.y);
}

//



template <class T>
T SMathX::GetLength(const SBaseVector2<T> &v)
{
    return SVec2Length(&v);
}
template <class T>
T SMathX::GetDot(const SBaseVector2<T> &v1, const SBaseVector2<T> &v2)
{
    return SVec2Dot(&v1, &v2);
}

template <class T>
T SMathX::GetCrossValue(const SBaseVector2<T> &v1, const SBaseVector2<T> &v2)
{
    return SVec2CrossValue(&v1, &v2);
}

template <class T>
SBaseVector3<T> SMathX::GetCross(const SBaseVector2<T> &v1, const SBaseVector2<T> &v2)
{
    return SVec2Cross(&v1, &v2);
}

template <class T>
T SMathX::GetAngle(const SBaseVector2<T> &v1, const SBaseVector2<T> &v2)
{
    return (T)SVec2Angle(&v1, &v2);
}

//////
template <class T>
T SMathX::GetDistance(const SBasePoint3<T> &a, const SBasePoint3<T> &b)
{
    return SPoint3Distance(&a, &b);
}

template <class T>
SBaseVector3<T> SMathX::GetVector(const SBasePoint3<T> &s, const SBasePoint3<T> &e)
{
    return SBaseVector3<T>(e.x - s.x, e.y - s.y, e.z - s.z);
}

//碰撞函数
template <class T>
bool SMathX::IsCollsion(const SBasePoint2<T> &pt1, const SBasePoint2<T> &pt2)
{
    if (pt1.x == pt2.x && pt1.y == pt2.y)
        return true;
    else return false;
}
template <class T>
bool SMathX::IsCollsion(const SBasePoint2<T> &pt, const SBaseRect<T> &rt)
{
    if (pt.x >= rt.left && pt.x <= rt.right && pt.y >= rt.top && pt.y <= rt.bottom) 
    {
        return true;
    }
    return false;
}
template <class T>
bool SMathX::IsCollsion(const SBaseRect<T> &rt1, const SBaseRect<T> &rt2)
{
    if ((rt1->top > rt2->top && rt1->top < rt2->bottom) ||
        (rt1->bottom > rt2->top && rt1->bottom < rt2->bottom))
    {
        if ((rt1->left > rt2->left && rt1->left < rt2->right) ||
            (rt1->right > rt2->left && rt1->right < rt2->right))
        {
            return true;
        }
    }
    if ((rt2->top > rt1->top && rt2->top < rt1->bottom) ||
        (rt2->bottom > rt1->top && rt2->bottom < rt1->bottom))
    {
        if ((rt2->left > rt1->left && rt2->left < rt1->right) ||
            (rt2->right > rt1->left && rt2->right < rt1->right))
        {
            return true;
        }
    }
    return false;
}

//是否在矩形内
template <class T>
bool SMathX::IsInRect(const SBasePoint2<T> &pt, const SBaseRect<T> &rt)
{
    if (pt.x > rt.left && pt.x < rt.right
        && pt.y > rt.top && pt.y < rt.bottom)
        return true;
    else
        return false;
}
template <class T>
bool SMathX::IsInRect(const SBaseRect<T> &rt1, const SBaseRect<T> &rt2)
{
    if (((rt1.left >= rt2.left) && (rt1.right <= rt2.right)) && ((rt1.top >= rt2.top) && (rt1.bottom <= rt2.bottom)))
        return true;
    else
        return false;
}

//在矩形上
template <class T>
bool SMathX::IsOnRect(const SBasePoint2<T> &pt, const SBaseRect<T> &rt)
{
    if (pt.x == rt.left || pt.x == rt.right)
    {
        if (pt.y >= rt.top && pt.y <= rt.bottom)
            return true;
        return false;
    }
    if (pt.y == rt.top || pt.y == rt.bottom)
    {
        if (pt.x >= rt.left && pt.x <= rt.right)
            return true;
        return false;
    }
    return false;
}

//////
template <class T>
T SMathX::GetLength(const SBaseVector3<T> &v)
{
    return SVec3Length(v);
}

template <class T>
T SMathX::GetDot(const SBaseVector3<T> &v1, const SBaseVector2<T> &v2)
{
    return SVec3Dot(v1, v2);
}

template <class T>
SBaseVector3<T> SMathX::GetCross(const SBaseVector3<T> &v1, const SBaseVector3<T> &v2)
{
    SBaseVector3<T> out;
    SVec3Cross(&out, v1, v2);
    return out;

}

template <class T>
T SMathX::GetAngle(const SBaseVector3<T> &v1, const SBaseVector3<T> &v2)
{
    return SVec3Angle(&v1, &v2);
}


//////
//////
/////
template <class T>
double SPoint2Distance(const SBasePoint2<T> *a, const SBasePoint2<T> *b)
{
    return hypot(a->x - b->x, a->y - b->y);
}

template <class T>
double SVec2Length(const SBaseVector2<T> *v)
{
    return sqrt(v->x * v->x + v->y * v->y);
}

template <class T>
T SVec2Dot(const SBaseVector2<T> *v1, const SBaseVector2<T> *v2)
{
    return (v1->x*v2->x + v1->y*v2->y);
}

template <class T>
T SVec2CrossValue(const SBaseVector2<T> *v1, const SBaseVector2<T> *v2)
{
    return (v1->x * v2->y - v1->y * v2->x);
}

template <class T>
SBaseVector3<T> SVec2Cross(const SBaseVector2<T> *v1, const SBaseVector2<T> *v2)
{
    return SBaseVector3<T>(
        0,
        0,
        GetCrossValue(v1, v2));
}

template <class T>
double SVec2Angle(const SBaseVector2<T> *v1, const SBaseVector2<T> *v2)
{
    //acos取值在0-Pi,因考虑顺逆时钟的情况
    T crossValue = SVec2CrossValue(v1,v2);
    double cos_theta = acos(SVec2Dot(v1, v2) / (SVec2Length(v1) * SVec2Length(v2)));
    if (crossValue < (T)0.f)
        return 2 * SMath::Pi - cos_theta;
    else
        return cos_theta;
}

template <class T>
void SVec2Normalize(SBaseVector2<T> *v)
{
    double Length = SVec2Length(v); //向量长度;  
    v->x /= Length;
    v->y /= Length;
}

template <class T>
bool SRectIntersect(const SBaseRect<T> *pSrcRt1, const SBaseRect<T> *pSrcRt2, SBaseRect<T> *pDstRt)
{
    if (pSrcRt1->left>pSrcRt2->left)
    {
        pDstRt->left = pSrcRt1->left;
    }
    else
    {
        pDstRt->left = pSrcRt2->left;
    }

    if (pSrcRt1->top>pSrcRt2->top)
    {
        pDstRt->top = pSrcRt1->top;
    }
    else
    {
        pDstRt->top = pSrcRt2->top;
    }

    if (pSrcRt1->right>pSrcRt2->right)
    {
        pDstRt->right = pSrcRt2->right;
    }
    else
    {
        pDstRt->right = pSrcRt1->right;
    }

    if (pSrcRt1->bottom>pSrcRt2->bottom)
    {
        pDstRt->bottom = pSrcRt2->bottom;
    }
    else
    {
        pDstRt->bottom = pSrcRt1->bottom;
    }
    if (pDstRt->left >= pDstRt->right || pDstRt->top >= pDstRt->bottom)
    {
        SetRectEmpty(pDstRt);
        return false;
    }
    else
    {
        return true;
    }
}

template <class T>
double SPoint3Distance(const SBasePoint3<T> *a, const SBasePoint3<T> *b)
{
    T sx = b->x - a->x;
    T sy = b->y - a->y;
    T sz = b->z - a->z;
    return sqrt(sx*sx + sy*sy + sz*sz);
}




//	创建2D的变换矩阵，就是在XY平面内变换矩阵。
//  Mout = (Msc)-1 * (Msr)-1 * Ms * Msr * Msc * (Mrc)-1 * Mr * Mrc * Mt
template <class T>
SBaseMatrix<T> *SMatrixTransformation2D(
    SBaseMatrix<T>			*pOut,						//要输出结构的变换矩阵
    const SBaseVector2<T>	*pScalingCenter,			//缩放中心向量。如果参数为NULL，Msc 矩阵为单位矩阵。
    float					pScalingRotation,			//指向缩放旋转系数。
    const SBaseVector2<T>	*pScaling,					//结构的缩放向量。如果参数为NULL，Ms矩阵为单位矩阵。
    const SBaseVector2<T>	*pRotationCenter,			//结构的旋转向量。如果参数为NULL，Mrc矩阵为单位矩阵。
    float					Rotation,					//旋转角度。
    const SBaseVector2<T>	*pTranslation				//结构的平移向量。如果参数为NULL，Mt矩阵为单位矩阵。
    )
{
    //这个函数用下面的公式计算变换矩阵：
    //    Mout = (Msc)-1 * (Msr)-1 * Ms * Msr * Msc * (Mrc)-1 * Mr * Mrc * Mt
    //其中 :
    //    Mout = 输出矩阵(pOut)
    //    Msc = 缩放中心矩阵(pScalingCenter)
    //    Msr = 缩放旋转矩阵(pScalingRotation)
    //    Ms = 缩放矩阵(pScaling)
    //    Mrc = 旋转矩阵的中心(pRotationCenter)
    //    Mr = 旋转矩阵(Rotation)
    //    Mt = 平移矩阵(pTranslation)
    SBaseMatrix<T> Msc_1;
    SBaseMatrix<T> Msr_1;
    SBaseMatrix<T> Ms;
    SBaseMatrix<T> Msr;
    SBaseMatrix<T> Msc;
    SBaseMatrix<T> Mrc_1;
    SBaseMatrix<T> Mr;
    SBaseMatrix<T> Mrc;
    SBaseMatrix<T> Mt;

    pScalingCenter ? SMatrixTranslation(&Msc, pScalingCenter->x, pScalingCenter->y, (T)0.f) : SMatrixIdentity(&Msc);
    SMatrixInverse(&Msc_1, (T *)nullptr, &Msc);
    pScaling ? SMatrixScaling(&Ms, pScaling->x, pScaling->y, (T)1.f) : SMatrixIdentity(&Ms);
    //TODO:缩放旋转矩阵是什么鬼?
    SMatrixRotationZ(&Msr, pScalingRotation);
    SMatrixInverse(&Msr_1, (T *)nullptr, &Msr);

    pRotationCenter ? SMatrixTranslation(&Mrc, pRotationCenter->x, pRotationCenter->y, (T)0.f) : SMatrixIdentity(&Mrc);
    SMatrixInverse(&Mrc_1, (T *)nullptr, &Mrc);
    SMatrixRotationZ(&Mr, Rotation);
    pTranslation ? SMatrixTranslation(&Mt, pTranslation->x, pTranslation->y, (T)0.f) : SMatrixIdentity(&Mt);

    SMatrixIdentity(pOut);
    SMatrixMultiply(pOut, pOut, &Msc_1);
    SMatrixMultiply(pOut, pOut, &Msr_1);
    SMatrixMultiply(pOut, pOut, &Ms);
    SMatrixMultiply(pOut, pOut, &Msr);
    SMatrixMultiply(pOut, pOut, &Msc);
    SMatrixMultiply(pOut, pOut, &Mrc_1);
    SMatrixMultiply(pOut, pOut, &Mr);
    SMatrixMultiply(pOut, pOut, &Mrc);
    SMatrixMultiply(pOut, pOut, &Mt);
    return pOut;
}


//2D向量扩展到4D，Z=0,W用1填充。然后与矩阵相乘
template <class T>
SBaseVector2<T> *SVec2TransformCoord(SBaseVector2<T> *pOut, const SBaseVector2<T> *pV, const SBaseMatrix<T> *pM)
{
    SBaseVector2<T> v;
    T w = 1;
    v.x = pV->x * pM->m[0] + pV->y * pM->m[4] + w*pM->m[12];
    v.y = pV->x * pM->m[1] + pV->y * pM->m[5] + w*pM->m[13];
    *pOut = v;
    return pOut;
}

//2D向量扩展到4D，Z=0,W用0填充。然后与矩阵相乘
template <class T>
SBaseVector2<T> *SVec3TransformNormal(SBaseVector2<T> *pOut, const SBaseVector2<T> *pV, const SBaseMatrix<T> *pM)
{
    SBaseVector2<T> v;
    T w = 0;
    pOut->x = pV->x * pM->m[0] + pV->y * pM->m[4] + w*pM->m[12];
    pOut->y = pV->x * pM->m[1] + pV->y * pM->m[5] + w*pM->m[13];
    *pOut = v;
    return pOut;
}


////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////


///
//向量叉乘
template <class T>
void SVec3Cross(SBaseVector3<T> *pOut, const SBaseVector3<T> *pV1, const SBaseVector3<T> *pV2)
{
    //声明临时变量是为了防止pOut==pV1;
    SBaseVector3<T> v;
    v.x = pV1->y * pV2->z - pV1->z * pV2->y;
    v.y = pV1->z * pV2->x - pV1->x * pV2->z;
    v.z = pV1->x * pV2->y - pV1->y * pV2->x;
    *pOut = v;
}

//向量规范化
template <class T>
void SVec3Normalize(SBaseVector3<T> *pOut, const SBaseVector3<T> *pV)
{
    SBaseVector3<T> &v = *pOut;
    T length = (T)SVec3Length(pV);
    v.x = pV->x / length;
    v.y = pV->y / length;
    v.z = pV->z / length;
}

//向量点乘
template <class T>
double SVec3Dot(const SBaseVector3<T> *pV1, const SBaseVector3<T> *pV2)
{
    return (pV1->x*pV2->x + pV1->y*pV2->y + pV1->z*pV2->z);
}

//向量长度
template <class T>
double SVec3Length(const SBaseVector3<T> *pV)
{
    return sqrt(pV->x * pV->x + pV->y * pV->y + pV->z * pV->z);
}

template <class T>
double SVec3Angle(const SBaseVector3<T> *pV1, const SBaseVector3<T> *pV2)
{
    //TODO:acos取值在0-Pi,因考虑顺逆时钟的情况
    return acos(SVec3Dot(pV1, pV2) /(SVec3Length(pV1) * SVec3Length(pV2)));
}

template <class T>
SBaseMatrix<T>* SMatrixMultiply(SBaseMatrix<T> *pOut, const SBaseMatrix<T> *pM1, const SBaseMatrix<T> *pM2)
{
    //矩阵乘法,不满足交换律,注意次序
    SBaseMatrix<T> mat;
    mat.m[0] = pM2->m[0] * pM1->m[0] + pM2->m[4] * pM1->m[1] + pM2->m[8] * pM1->m[2] + pM2->m[12] * pM1->m[3];
    mat.m[1] = pM2->m[1] * pM1->m[0] + pM2->m[5] * pM1->m[1] + pM2->m[9] * pM1->m[2] + pM2->m[13] * pM1->m[3];
    mat.m[2] = pM2->m[2] * pM1->m[0] + pM2->m[6] * pM1->m[1] + pM2->m[10] * pM1->m[2] + pM2->m[14] * pM1->m[3];
    mat.m[3] = pM2->m[3] * pM1->m[0] + pM2->m[7] * pM1->m[1] + pM2->m[11] * pM1->m[2] + pM2->m[15] * pM1->m[3];
    mat.m[4] = pM2->m[0] * pM1->m[4] + pM2->m[4] * pM1->m[5] + pM2->m[8] * pM1->m[6] + pM2->m[12] * pM1->m[7];
    mat.m[5] = pM2->m[1] * pM1->m[4] + pM2->m[5] * pM1->m[5] + pM2->m[9] * pM1->m[6] + pM2->m[13] * pM1->m[7];
    mat.m[6] = pM2->m[2] * pM1->m[4] + pM2->m[6] * pM1->m[5] + pM2->m[10] * pM1->m[6] + pM2->m[14] * pM1->m[7];
    mat.m[7] = pM2->m[3] * pM1->m[4] + pM2->m[7] * pM1->m[5] + pM2->m[11] * pM1->m[6] + pM2->m[15] * pM1->m[7];
    mat.m[8] = pM2->m[0] * pM1->m[8] + pM2->m[4] * pM1->m[9] + pM2->m[8] * pM1->m[10] + pM2->m[12] * pM1->m[11];
    mat.m[9] = pM2->m[1] * pM1->m[8] + pM2->m[5] * pM1->m[9] + pM2->m[9] * pM1->m[10] + pM2->m[13] * pM1->m[11];
    mat.m[10] = pM2->m[2] * pM1->m[8] + pM2->m[6] * pM1->m[9] + pM2->m[10] * pM1->m[10] + pM2->m[14] * pM1->m[11];
    mat.m[11] = pM2->m[3] * pM1->m[8] + pM2->m[7] * pM1->m[9] + pM2->m[11] * pM1->m[10] + pM2->m[15] * pM1->m[11];
    mat.m[12] = pM2->m[0] * pM1->m[12] + pM2->m[4] * pM1->m[13] + pM2->m[8] * pM1->m[14] + pM2->m[12] * pM1->m[15];
    mat.m[13] = pM2->m[1] * pM1->m[12] + pM2->m[5] * pM1->m[13] + pM2->m[9] * pM1->m[14] + pM2->m[13] * pM1->m[15];
    mat.m[14] = pM2->m[2] * pM1->m[12] + pM2->m[6] * pM1->m[13] + pM2->m[10] * pM1->m[14] + pM2->m[14] * pM1->m[15];
    mat.m[15] = pM2->m[3] * pM1->m[12] + pM2->m[7] * pM1->m[13] + pM2->m[11] * pM1->m[14] + pM2->m[15] * pM1->m[15];
    *pOut = mat;
    return pOut;
}

//绕任意向量旋转的矩阵
template <class T>
SBaseMatrix<T>* SMatrixRotationAxis(SBaseMatrix<T> *pOut, const SBaseVector3<T> *pV, T Angle)
{
    //由于DX9中的三角函数经过优化,因此在精度上可能不如库函数的一致
    SVec3Normalize((SBaseVector3<T> *)pV, pV);

    T u = pV->x;
    T v = pV->y;
    T w = pV->z;

    pOut->m[0] = cos(Angle) + (u * u) * (1 - cos(Angle));
    pOut->m[1] = u * v * (1 - cos(Angle)) + w * sin(Angle);
    pOut->m[2] = u * w * (1 - cos(Angle)) - v * sin(Angle);
    pOut->m[3] = 0;

    pOut->m[4] = u * v * (1 - cos(Angle)) - w * sin(Angle);
    pOut->m[5] = cos(Angle) + v * v * (1 - cos(Angle));
    pOut->m[6] = w * v * (1 - cos(Angle)) + u * sin(Angle);
    pOut->m[7] = 0;

    pOut->m[8] = u * w * (1 - cos(Angle)) + v * sin(Angle);
    pOut->m[9] = v * w * (1 - cos(Angle)) - u * sin(Angle);
    pOut->m[10] = cos(Angle) + w * w * (1 - cos(Angle));
    pOut->m[11] = 0;

    pOut->m[12] = 0;
    pOut->m[13] = 0;
    pOut->m[14] = 0;
    pOut->m[15] = 1;

    return pOut;
}

template <class T>
SBaseMatrix<T>* SMatrixRotationLine(SBaseMatrix<T> *pOut, SBaseVector3<T> *pV1, SBaseVector3<T> *pV2, T Angle)
{
    T a = pV1->x;
    T b = pV1->y;
    T c = pV1->z;

    SBaseVector3<T> p = *pV2 - *pV1;
    SVec3Normalize(&p, &p);
    T u = p.x;
    T v = p.y;
    T w = p.z;

    T uu = u * u;
    T uv = u * v;
    T uw = u * w;
    T vv = v * v;
    T vw = v * w;
    T ww = w * w;
    T au = a * u;
    T av = a * v;
    T aw = a * w;
    T bu = b * u;
    T bv = b * v;
    T bw = b * w;
    T cu = c * u;
    T cv = c * v;
    T cw = c * w;

    T costheta = cos(theta);
    T sintheta = sin(theta);

    pOut->m[0] = uu + (vv + ww) * costheta;
    pOut->m[1] = uv * (1 - costheta) + w * sintheta;
    pOut->m[2] = uw * (1 - costheta) - v * sintheta;
    pOut->m[3] = 0;

    pOut->m[4] = uv * (1 - costheta) - w * sintheta;
    pOut->m[5] = vv + (uu + ww) * costheta;
    pOut->m[6] = vw * (1 - costheta) + u * sintheta;
    pOut->m[7] = 0;

    pOut->m[8] = uw * (1 - costheta) + v * sintheta;
    pOut->m[9] = vw * (1 - costheta) - u * sintheta;
    pOut->m[10] = ww + (uu + vv) * costheta;
    pOut->m[11] = 0;

    pOut->m[12] = (a * (vv + ww) - u * (bv + cw)) * (1 - costheta) + (bw - cv) * sintheta;
    pOut->m[13] = (b * (uu + ww) - v * (au + cw)) * (1 - costheta) + (cu - aw) * sintheta;
    pOut->m[14] = (c * (uu + vv) - w * (au + bv)) * (1 - costheta) + (av - bu) * sintheta;
    pOut->m[15] = 1;

    return pOut;
}

//3D向量扩展到4D，W用1填充。然后与矩阵相乘
template <class T>
SBaseVector3<T> *SVec3TransformCoord(SBaseVector3<T> *pOut, const SBaseVector3<T> *pV, const SBaseMatrix<T> *pM)
{
    SBaseVector3<T> v;
    T w = 1;
    v.x = pV->x * pM->m[0] + pV->y * pM->m[4] + pV->z * pM->m[8] + w*pM->m[12];
    v.y = pV->x * pM->m[1] + pV->y * pM->m[5] + pV->z * pM->m[9] + w*pM->m[13];
    v.z = pV->x * pM->m[2] + pV->y * pM->m[6] + pV->z * pM->m[10] + w*pM->m[14];
    *pOut = v;
    return pOut;
}

//3D向量扩展到4D，W用0填充。然后与矩阵相乘
template <class T>
SBaseVector3<T> *SVec3TransformNormal(SBaseVector3<T> *pOut, const SBaseVector3<T> *pV, const SBaseMatrix<T> *pM)
{
    SBaseVector3<T> v;
    T w = 0;
    pOut->x = pV->x * pM->m[0] + pV->y * pM->m[4] + pV->z * pM->m[8] + w*pM->m[12];
    pOut->y = pV->x * pM->m[1] + pV->y * pM->m[5] + pV->z * pM->m[9] + w*pM->m[13];
    pOut->z = pV->x * pM->m[2] + pV->y * pM->m[6] + pV->z * pM->m[10] + w*pM->m[14];
    *pOut = v;
    return pOut;
}

//获得指定参数的透视投影矩阵，用于3D投影变换。
template <class T>
SBaseMatrix<T>* SMatrixPerspectiveFovLH(SBaseMatrix<T> *pOut, T fovy, T Aspect, T zn, T zf)
{
    T yScale = 1 / tan(fovy / 2);
    T xScale = yScale / Aspect;

    pOut->m[0] = xScale;
    pOut->m[1] = 0;
    pOut->m[2] = 0;
    pOut->m[3] = 0;

    pOut->m[4] = 0;
    pOut->m[5] = yScale;
    pOut->m[6] = 0;
    pOut->m[7] = 0;

    pOut->m[8] = 0;
    pOut->m[9] = 0;
    pOut->m[10] = zf / (zf - zn);
    pOut->m[11] = 1;

    pOut->m[12] = 0;
    pOut->m[13] = 0;
    pOut->m[14] = -zn * zf / (zf - zn);
    pOut->m[15] = 0;

    return pOut;

}

template <class T>
SBaseMatrix<T>* SMatrixOrthoLH(SBaseMatrix<T> *pOut, T w, T h, T zn, T zf)
{
    pOut->m[0] = 2 / w;
    pOut->m[1] = 0;
    pOut->m[2] = 0;
    pOut->m[3] = 0;

    pOut->m[4] = 0;
    pOut->m[5] = 2 / h;
    pOut->m[6] = 0;
    pOut->m[7] = 0;

    pOut->m[8] = 0;
    pOut->m[9] = 0;
    pOut->m[10] = 1 / (zf - zn);
    pOut->m[11] = 0;

    pOut->m[12] = 0;
    pOut->m[13] = 0;
    pOut->m[14] = zn / (zn - zf);
    pOut->m[15] = 0;

    return pOut;
}

template <class T>
SBaseMatrix<T> * SMatrixPerspectiveOffCenterLH(SBaseMatrix<T> * pOut, T l, T r, T b, T t, T zn, T zf)
{
    pOut->m[0] = 2 * zn / (r - l);
    pOut->m[1] = 0;
    pOut->m[2] = 0;
    pOut->m[3] = 0;

    pOut->m[4] = 0;
    pOut->m[5] = 2 * zn / (t - b);
    pOut->m[6] = 0;
    pOut->m[7] = 0;

    pOut->m[8] = (l + r) / (l - r);
    pOut->m[9] = (t + b) / (b - t);
    pOut->m[10] = zf / (zf - zn);
    pOut->m[11] = 1;

    pOut->m[12] = 0;
    pOut->m[13] = 0;
    pOut->m[14] = zn*zf / (zn - zf);
    pOut->m[15] = 0;

    return pOut;
}

//生成绕X轴旋转的矩阵
template <class T>
SBaseMatrix<T>* SMatrixRotationX(SBaseMatrix<T> *pOut, T Angle)
{
    pOut->m[0] = 1;
    pOut->m[1] = 0;
    pOut->m[2] = 0;
    pOut->m[3] = 0;

    pOut->m[4] = 0;
    pOut->m[5] = cos(Angle);
    pOut->m[6] = sin(Angle);
    pOut->m[7] = 0;

    pOut->m[8] = 0;
    pOut->m[9] = -sin(Angle);
    pOut->m[10] = cos(Angle);
    pOut->m[11] = 0;

    pOut->m[12] = 0;
    pOut->m[13] = 0;
    pOut->m[14] = 0;
    pOut->m[15] = 1;

    return pOut;
}

//生成绕Y轴旋转的矩阵
template <class T>
SBaseMatrix<T>* SMatrixRotationY(SBaseMatrix<T> *pOut, T Angle)
{
    pOut->m[0] = cos(Angle);
    pOut->m[1] = 0;
    pOut->m[2] = -sin(Angle);
    pOut->m[3] = 0;

    pOut->m[4] = 0;
    pOut->m[5] = 1;
    pOut->m[6] = 0;
    pOut->m[7] = 0;

    pOut->m[8] = sin(Angle);
    pOut->m[9] = 0;
    pOut->m[10] = cos(Angle);
    pOut->m[11] = 0;

    pOut->m[12] = 0;
    pOut->m[13] = 0;
    pOut->m[14] = 0;
    pOut->m[15] = 1;

    return pOut;
}

//生成绕Z轴旋转的矩阵
template <class T>
SBaseMatrix<T>* SMatrixRotationZ(SBaseMatrix<T> *pOut, T Angle)
{

    pOut->m[0] = cos(Angle);
    pOut->m[1] = sin(Angle);
    pOut->m[2] = 0;
    pOut->m[3] = 0;

    pOut->m[4] = -sin(Angle);
    pOut->m[5] = cos(Angle);
    pOut->m[6] = 0;
    pOut->m[7] = 0;

    pOut->m[8] = 0;
    pOut->m[9] = 0;
    pOut->m[10] = 1;
    pOut->m[11] = 0;

    pOut->m[12] = 0;
    pOut->m[13] = 0;
    pOut->m[14] = 0;
    pOut->m[15] = 1;

    return pOut;
}

//创建一个单位矩阵
template <class T>
SBaseMatrix<T>* SMatrixIdentity(SBaseMatrix<T> *pOut)
{
    pOut->m[0] = 1;
    pOut->m[1] = 0;
    pOut->m[2] = 0;
    pOut->m[3] = 0;

    pOut->m[4] = 0;
    pOut->m[5] = 1;
    pOut->m[6] = 0;
    pOut->m[7] = 0;

    pOut->m[8] = 0;
    pOut->m[9] = 0;
    pOut->m[10] = 1;
    pOut->m[11] = 0;

    pOut->m[12] = 0;
    pOut->m[13] = 0;
    pOut->m[14] = 0;
    pOut->m[15] = 1;

    return pOut;
}

//计算矩阵的逆矩阵
template <class T>
SBaseMatrix<T>* SMatrixInverse(SBaseMatrix<T> *pOut, T *pDeterminant, const SBaseMatrix<T> *pM)
{
    //TODO:有待更正-无法判断是否存在逆
    //如果没有逆则返回nullptr

    int n = 4;
    int i, j, k, m = 2 * n;
    T mik, temp;
    T **a = new T*[n];

    for (i = 0; i<n; i++)
    {
        a[i] = new T[2 * n];
    }

    //初始化B=E
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i == j)
                pOut->m[i*n + j] = pDeterminant ? pDeterminant[i] : 1.0f;
            else
                pOut->m[i*n + j] = 0.0f;
        }
    }

    for (i = 0; i<n; i++)
        for (j = 0; j<n; j++)
            a[i][j] = pM->m[i*n+j];           //复制A到a，避免改变A的值

    for (i = 0; i<n; i++)
        for (j = n; j<m; j++)
            a[i][j] = pOut->m[i*n + j - n];  //复制B到a，增广矩阵

    //顺序高斯消去法化左下角为零
    for (k = 1; k <= n - 1; k++)
    {
        for (i = k + 1; i <= n; i++)
        {
            mik = a[i - 1][k - 1] / a[k - 1][k - 1];
            for (j = k + 1; j <= m; j++)
            {
                a[i - 1][j - 1] -= mik*a[k - 1][j - 1];
            }
        }
    }

    //归一化
    for (i = 1; i <= n; i++)
    {
        temp = a[i - 1][i - 1];
        for (j = 1; j <= m; j++)
        {
            a[i - 1][j - 1] /= temp;
        }
    }

    //逆序高斯消去法化增广矩阵左边为单位矩阵
    for (k = n - 1; k >= 1; k--)
    {
        for (i = k; i >= 1; i--)
        {
            mik = a[i - 1][k];
            for (j = k + 1; j <= m; j++)
            {
                a[i - 1][j - 1] -= mik*a[k][j - 1];
            }
        }
    }        

    for (i = 0; i<n; i++)
        for (j = 0; j<n; j++)
            pOut->m[i*n + j] = a[i][j + n];  //取出求逆结果

    for (i = 0; i<n; i++)
        for (j = 0; j<n; j++)
            if (fabs(pOut->m[i*n + j])<0.0001f)
                pOut->m[i*n + j] = 0.0f;

    for (i = 0; i<n; i++)
    {
        delete[] a[i] ;
    }
    delete[]a;

    return pOut;
}

//计算矩阵的转置矩阵
template <class T>
SBaseMatrix<T>* SMatrixTranspose(SBaseMatrix<T> *pOut, const SBaseMatrix<T> *pM)
{
    SBaseMatrix<T> m;
    m.m[0] = pM->m[0];
    m.m[1] = pM->m[4];
    m.m[2] = pM->m[8];
    m.m[3] = pM->m[12];

    m.m[4] = pM->m[1];
    m.m[5] = pM->m[5];
    m.m[6] = pM->m[9];
    m.m[7] = pM->m[13];

    m.m[8] = pM->m[2];
    m.m[9] = pM->m[6];
    m.m[10] = pM->m[10];
    m.m[11] = pM->m[14];

    m.m[12] = pM->m[3];
    m.m[13] = pM->m[7];
    m.m[14] = pM->m[11];
    m.m[15] = pM->m[15];
    *pOut = v;
    return pOut;
}

//创建一个沿着X,Y和Z轴方向缩放矩阵
template <class T>
SBaseMatrix<T>* SMatrixScaling(SBaseMatrix<T> *pOut, T sx, T sy, T sz)
{
    pOut->m[0] = sx;
    pOut->m[1] = 0;
    pOut->m[2] = 0;
    pOut->m[3] = 0;

    pOut->m[4] = 0;
    pOut->m[5] = sy;
    pOut->m[6] = 0;
    pOut->m[7] = 0;

    pOut->m[8] = 0;
    pOut->m[9] = 0;
    pOut->m[10] = sz;
    pOut->m[11] = 0;

    pOut->m[12] = 0;
    pOut->m[13] = 0;
    pOut->m[14] = 0;
    pOut->m[15] = 1;

    return pOut;
}

// 创建一个沿着X,Y和Z轴方向平移矩阵
template <class T>
SBaseMatrix<T>* SMatrixTranslation(SBaseMatrix<T> *pOut, T x, T y, T z)
{
    pOut->m[0] = 1;
    pOut->m[1] = 0;
    pOut->m[2] = 0;
    pOut->m[3] = 0;

    pOut->m[4] = 0;
    pOut->m[5] = 1;
    pOut->m[6] = 0;
    pOut->m[7] = 0;

    pOut->m[8] = 0;
    pOut->m[9] = 0;
    pOut->m[10] = 1;
    pOut->m[11] = 0;

    pOut->m[12] = x;
    pOut->m[13] = y;
    pOut->m[14] = z;
    pOut->m[15] = 1;

    return pOut;
}

//创建一个变换矩阵。如果参数设置为NULL，就当作单位矩阵处理。
template <class T>
SBaseMatrix<T> *SMatrixTransformation(
    SBaseMatrix<T>				*pOut,
    const SBaseVector3<T>		*pScalingCenter,	//结构的缩放中心向量。如果参数为NULL，Msc 矩阵为单位矩阵。
    const SBaseQuaternion<T>	*pScalingRotation,	//指向缩放旋转系数。
    const SBaseVector3<T>		*pScaling,			//缩放向量。如果参数为NULL，Ms矩阵为单位矩阵。
    const SBaseVector3<T>		*pRotationCenter,	//旋转向量。如果参数为NULL，Mrc矩阵为单位矩阵。
    const SBaseQuaternion<T>	*pRotation,			//旋转角度。
    const SBaseVector3<T>		*pTranslation		//平移向量。如果参数为NULL，Mt矩阵为单位矩阵。
    )
{
    //这个函数用下面的公式计算变换矩阵：
    //    Mout = (Msc)-1 * (Msr)-1 * Ms * Msr * Msc * (Mrc)-1 * Mr * Mrc * Mt
    //其中 :
    //    Mout = 输出矩阵(pOut)
    //    Msc = 缩放中心矩阵(pScalingCenter)
    //    Msr = 缩放旋转矩阵(pScalingRotation)
    //    Ms = 缩放矩阵(pScaling)
    //    Mrc = 旋转矩阵的中心(pRotationCenter)
    //    Mr = 旋转矩阵(Rotation)
    //    Mt = 平移矩阵(pTranslation)
    SBaseMatrix<T> Msc_1;
    SBaseMatrix<T> Msr_1;
    SBaseMatrix<T> Ms;
    SBaseMatrix<T> Msr;
    SBaseMatrix<T> Msc;
    SBaseMatrix<T> Mrc_1;
    SBaseMatrix<T> Mr;
    SBaseMatrix<T> Mrc;
    SBaseMatrix<T> Mt;

    pScalingCenter ? SMatrixTranslation(&Msc, pScalingCenter->x, pScalingCenter->y, pScalingCenter->z) : SMatrixIdentity(&Msc);
    SMatrixInverse(&Msc_1, (T *)nullptr, &Msc);
    pScalingRotation ? SMatrixRotationAxis(&Msr, SBaseVector3<T>(pScalingRotation->x, pScalingRotation->y, pScalingRotation->z), pScalingRotation->w) : SMatrixIdentity(&Msc);
    SMatrixInverse(&Msr_1, (T *)nullptr, &Msr);
    pScaling ? SMatrixScaling(&Ms, pScaling->x, pScaling->y, pScaling->z) : SMatrixIdentity(&Ms);
    //TODO:缩放旋转系数什么鬼
    pRotationCenter ? SMatrixTranslation(&Mrc, pRotationCenter->x, pRotationCenter->y, pRotationCenter->z) : SMatrixIdentity(&Mrc);
    SMatrixInverse(&Mrc_1, (T *)nullptr, &Mrc);

    pRotation ? SMatrixRotationAxis(&Mr, SBaseVector3<T>(pRotation->x, pRotation->y, pRotation->z), pRotation->w) : SMatrixIdentity(&Mr);
    pTranslation ? SMatrixTranslation(&Mt, pTranslation->x, pTranslation->y, pTranslation->z) : SMatrixIdentity(&Mt);
    
    SMatrixIdentity(pOut);
    SMatrixMultiply(pOut, pOut, &Msc_1);
    SMatrixMultiply(pOut, pOut, &Msr_1);
    SMatrixMultiply(pOut, pOut, &Ms);
    SMatrixMultiply(pOut, pOut, &Msr);
    SMatrixMultiply(pOut, pOut, &Msc);
    SMatrixMultiply(pOut, pOut, &Mrc_1);
    SMatrixMultiply(pOut, pOut, &Mr);
    SMatrixMultiply(pOut, pOut, &Mrc);
    SMatrixMultiply(pOut, pOut, &Mt);

    return pOut;
}

//创建一个仿射变换变换矩阵。NULL的参数就会当作是单位矩阵。
template <class T>
SBaseMatrix<T> *SMatrixAffineTransformation(
    SBaseMatrix<T>				*pOut,				//返回结果的矩阵。	
    float						Scaling,			//缩放系数。
    const SBaseVector3<T>		*pRotationCenter,	//旋转中心向量。如果设置为NULL，就用一个单位矩阵代替Mrc 。
    const SBaseQuaternion<T>	*pRotation,			//旋转矩阵。如果参数为NULL，就用单位矩阵Mr 代替。
    const SBaseVector3<T>		*pTranslation		//变换向量。如果为NULL，就用单位矩阵Mt 。
    )
{

    //TODO::

    return pOut;
}
#endif