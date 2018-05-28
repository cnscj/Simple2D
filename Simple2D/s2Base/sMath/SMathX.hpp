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
    //��ײ����
    template <class T>
    bool IsCollsion(const SBasePoint2<T> &pt1,const SBasePoint2<T> &pt2);
    template <class T>
    bool IsCollsion(const SBasePoint2<T> &pt, const SBaseRect<T> &rt);
    template <class T>
    bool IsCollsion(const SBaseRect<T> &rt1, const SBaseRect<T> &rt2);

    //�Ƿ��ھ�����
    template <class T>
    bool IsInRect(const SBasePoint2<T> &pt, const SBaseRect<T> &rt);
    template <class T>
    bool IsInRect(const SBaseRect<T> &rt1, const SBaseRect<T> &rt2);

    //�ھ�����
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
///				������2γ�����			     ///
////////////////////////////////////////////////

template <class T>
double SPoint2Distance(const SBasePoint2<T> *a, const SBasePoint2<T> *b);


////////////////////////////////////////////////
///				������2γ��������			 ///
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
///				������2γ���β���			 ///
////////////////////////////////////////////////

//���������ε���ײ����
template <class T>
bool SRectIntersect(const SBaseRect<T> *pSrcRt1, const SBaseRect<T> *pSrcRt2, SBaseRect<T> *pDstRt);

////////////////////////////////////////////////
///				������2ά�������			 ///
////////////////////////////////////////////////
//����2D�ı任���󣬾�����XYƽ���ڱ任�����������ΪNULL�͵�����λ���󿴴���
template <class T>
SBaseMatrix<T> *SMatrixTransformation2D(
    SBaseMatrix<T>			*pOut,						//Ҫ����ṹ�ı任����
    const SBaseVector2<T>	*pScalingCenter,			//���������������������ΪNULL��Msc ����Ϊ��λ����
    float					pScalingRotation,			//ָ��������תϵ����
    const SBaseVector2<T>	*pScaling,					//�ṹ�������������������ΪNULL��Ms����Ϊ��λ����
    const SBaseVector2<T>	*pRotationCenter,			//�ṹ����ת�������������ΪNULL��Mrc����Ϊ��λ����
    float					Rotation,					//��ת�Ƕȡ�
    const SBaseVector2<T>	*pTranslation				//�ṹ��ƽ���������������ΪNULL��Mt����Ϊ��λ����
    );

//����һ������任�任����NULL�Ĳ����ͻᵱ���ǵ�λ����
template <class T>
SBaseMatrix<T> *SMatrixAffineTransformation2D(
    SBaseMatrix<T>			*pOut,
    float                   Scaling,
    const SBaseVector2<T>   *pRotationCenter,
    float                   Rotation,
    const SBaseVector2<T>   *pTranslation
    );

//2D������չ��4D��Z=0,W��1��䡣Ȼ����������
template <class T>
SBaseVector2<T> *SVec2TransformCoord(SBaseVector2<T> *pOut, const SBaseVector2<T> *pV, const SBaseMatrix<T> *pM);

//2D������չ��4D��Z=0,W��0��䡣Ȼ����������
template <class T>
SBaseVector2<T> *SVec3TransformNormal(SBaseVector2<T> *pOut, const SBaseVector2<T> *pV, const SBaseMatrix<T> *pM);


////////////////////////////////////////////////
///				������3γ�����			     ///
////////////////////////////////////////////////


template <class T>
double SPoint3Distance(const SBasePoint3<T> *a, const SBasePoint3<T> *b);


////////////////////////////////////////////////
///				������3ά��������			 ///
////////////////////////////////////////////////

//�������
template <class T>
void SVec3Cross(SBaseVector3<T> *pOut, const SBaseVector3<T> *pV1, const SBaseVector3<T> *pV2);

//�����淶��
template <class T>
void SVec3Normalize(SBaseVector3<T> *pOut, const SBaseVector3<T> *pV);

//�������
template <class T>
double SVec3Dot(const SBaseVector3<T> *pV1, const SBaseVector3<T> *pV2);

//��������
template <class T>
double SVec3Length(const SBaseVector3<T> *pV);

//ȡ�������н�(����)
template <class T>
double SVec3Angle(const SBaseVector3<T> *pV1, const SBaseVector3<T> *pV2);
////////////////////////////////////////////////
///				������3ά�������			 ///
////////////////////////////////////////////////
//�����������
template <class T>
SBaseMatrix<T>* SMatrixMultiply(SBaseMatrix<T> *pOut, const SBaseMatrix<T> *pM1, const SBaseMatrix<T> *pM2);

/* ���±仯ȫ���������ֶ��� */
//������������ת�ľ���
template <class T>
SBaseMatrix<T>* SMatrixRotationAxis(SBaseMatrix<T> *pOut, const SBaseVector3<T> *pV, T Angle);

//�����������˵���ת�ľ���
template <class T>
SBaseMatrix<T>* SMatrixRotationLine(SBaseMatrix<T> *pOut, SBaseVector3<T> *pV1, SBaseVector3<T> *pV2, T Angle);

//3D������չ��4D��W��1��䡣Ȼ����������
template <class T>
SBaseVector3<T> *SVec3TransformCoord(SBaseVector3<T> *pOut, const SBaseVector3<T> *pV, const SBaseMatrix<T> *pM);

//3D������չ��4D��W��0��䡣Ȼ����������
template <class T>
SBaseVector3<T> *SVec3TransformNormal(SBaseVector3<T> *pOut, const SBaseVector3<T> *pV, const SBaseMatrix<T> *pM);

//���ָ��������͸��ͶӰ��������3DͶӰ�任��
template <class T>
SBaseMatrix<T>* SMatrixPerspectiveFovLH(SBaseMatrix<T> *pOut, T fovy, T Aspect, T zn, T zf);

//������ͼ���굽ͶӰ����ϵ��2Dת����
template <class T>
SBaseMatrix<T>* SMatrixOrthoLH(SBaseMatrix<T> *pOut, T w, T h, T zn, T zf);

//���ָ��������͸��ͶӰ��������3DͶӰ�任��
template <class T>
SBaseMatrix<T> * SMatrixPerspectiveOffCenterLH(SBaseMatrix<T> * pOut, T l, T r, T b, T t, T zn, T zf);

//������X����ת�ľ���
template <class T>
SBaseMatrix<T>* SMatrixRotationX(SBaseMatrix<T> *pOut, T Angle);

//������Y����ת�ľ���
template <class T>
SBaseMatrix<T>* SMatrixRotationY(SBaseMatrix<T> *pOut, T Angle);

//������Z����ת�ľ���
template <class T>
SBaseMatrix<T>* SMatrixRotationZ(SBaseMatrix<T> *pOut, T Angle);

//����һ����λ����
template <class T>
SBaseMatrix<T>* SMatrixIdentity(SBaseMatrix<T> *pOut);

//TODO:�㷨��д
//�������������()T
template <class T>
SBaseMatrix<T>* SMatrixInverse(SBaseMatrix<T> *pOut, T *pDeterminant, const SBaseMatrix<T> *pM);

//��������ת�þ���()-1
template <class T>
SBaseMatrix<T>* SMatrixTranspose(SBaseMatrix<T> *pOut, const SBaseMatrix<T> *pM);

//����һ������X,Y��Z�᷽�����ž���
template <class T>
SBaseMatrix<T>* SMatrixScaling(SBaseMatrix<T> *pOut, T sx, T sy, T sz);

//����һ������X,Y��Z�᷽��ƽ�ƾ���
template <class T>
SBaseMatrix<T>* SMatrixTranslation(SBaseMatrix<T> *pOut, T x, T y, T z);

//����һ���任���������������ΪNULL���͵�����λ������
template <class T>
SBaseMatrix<T> *SMatrixTransformation(
    SBaseMatrix<T>				*pOut,
    const SBaseVector3<T>		*pScalingCenter,	//�ṹ�����������������������ΪNULL��Msc ����Ϊ��λ����
    const SBaseQuaternion<T>	*pScalingRotation,	//ָ��������תϵ����
    const SBaseVector3<T>		*pScaling,			//�����������������ΪNULL��Ms����Ϊ��λ����
    const SBaseVector3<T>		*pRotationCenter,	//��ת�������������ΪNULL��Mrc����Ϊ��λ����
    const SBaseQuaternion<T>	pRotation,			//��ת�Ƕȡ�
    const SBaseVector3<T>		*pTranslation		//ƽ���������������ΪNULL��Mt����Ϊ��λ����
    );

//����һ������任�任����NULL�Ĳ����ͻᵱ���ǵ�λ����
template <class T>
SBaseMatrix<T> *SMatrixAffineTransformation(
    SBaseMatrix<T>				*pOut,				//���ؽ���ľ���	
    float						Scaling,			//����ϵ����
    const SBaseVector3<T>		*pRotationCenter,	//��ת�����������������ΪNULL������һ����λ�������Mrc ��
    const SBaseQuaternion<T>	*pRotation,			//��ת�����������ΪNULL�����õ�λ����Mr ���档
    const SBaseVector3<T>		*pTranslation		//�任���������ΪNULL�����õ�λ����Mt ��
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

//��ײ����
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

//�Ƿ��ھ�����
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

//�ھ�����
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
    //acosȡֵ��0-Pi,����˳��ʱ�ӵ����
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
    double Length = SVec2Length(v); //��������;  
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




//	����2D�ı任���󣬾�����XYƽ���ڱ任����
//  Mout = (Msc)-1 * (Msr)-1 * Ms * Msr * Msc * (Mrc)-1 * Mr * Mrc * Mt
template <class T>
SBaseMatrix<T> *SMatrixTransformation2D(
    SBaseMatrix<T>			*pOut,						//Ҫ����ṹ�ı任����
    const SBaseVector2<T>	*pScalingCenter,			//���������������������ΪNULL��Msc ����Ϊ��λ����
    float					pScalingRotation,			//ָ��������תϵ����
    const SBaseVector2<T>	*pScaling,					//�ṹ�������������������ΪNULL��Ms����Ϊ��λ����
    const SBaseVector2<T>	*pRotationCenter,			//�ṹ����ת�������������ΪNULL��Mrc����Ϊ��λ����
    float					Rotation,					//��ת�Ƕȡ�
    const SBaseVector2<T>	*pTranslation				//�ṹ��ƽ���������������ΪNULL��Mt����Ϊ��λ����
    )
{
    //�������������Ĺ�ʽ����任����
    //    Mout = (Msc)-1 * (Msr)-1 * Ms * Msr * Msc * (Mrc)-1 * Mr * Mrc * Mt
    //���� :
    //    Mout = �������(pOut)
    //    Msc = �������ľ���(pScalingCenter)
    //    Msr = ������ת����(pScalingRotation)
    //    Ms = ���ž���(pScaling)
    //    Mrc = ��ת���������(pRotationCenter)
    //    Mr = ��ת����(Rotation)
    //    Mt = ƽ�ƾ���(pTranslation)
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
    //TODO:������ת������ʲô��?
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


//2D������չ��4D��Z=0,W��1��䡣Ȼ����������
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

//2D������չ��4D��Z=0,W��0��䡣Ȼ����������
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
//�������
template <class T>
void SVec3Cross(SBaseVector3<T> *pOut, const SBaseVector3<T> *pV1, const SBaseVector3<T> *pV2)
{
    //������ʱ������Ϊ�˷�ֹpOut==pV1;
    SBaseVector3<T> v;
    v.x = pV1->y * pV2->z - pV1->z * pV2->y;
    v.y = pV1->z * pV2->x - pV1->x * pV2->z;
    v.z = pV1->x * pV2->y - pV1->y * pV2->x;
    *pOut = v;
}

//�����淶��
template <class T>
void SVec3Normalize(SBaseVector3<T> *pOut, const SBaseVector3<T> *pV)
{
    SBaseVector3<T> &v = *pOut;
    T length = (T)SVec3Length(pV);
    v.x = pV->x / length;
    v.y = pV->y / length;
    v.z = pV->z / length;
}

//�������
template <class T>
double SVec3Dot(const SBaseVector3<T> *pV1, const SBaseVector3<T> *pV2)
{
    return (pV1->x*pV2->x + pV1->y*pV2->y + pV1->z*pV2->z);
}

//��������
template <class T>
double SVec3Length(const SBaseVector3<T> *pV)
{
    return sqrt(pV->x * pV->x + pV->y * pV->y + pV->z * pV->z);
}

template <class T>
double SVec3Angle(const SBaseVector3<T> *pV1, const SBaseVector3<T> *pV2)
{
    //TODO:acosȡֵ��0-Pi,����˳��ʱ�ӵ����
    return acos(SVec3Dot(pV1, pV2) /(SVec3Length(pV1) * SVec3Length(pV2)));
}

template <class T>
SBaseMatrix<T>* SMatrixMultiply(SBaseMatrix<T> *pOut, const SBaseMatrix<T> *pM1, const SBaseMatrix<T> *pM2)
{
    //����˷�,�����㽻����,ע�����
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

//������������ת�ľ���
template <class T>
SBaseMatrix<T>* SMatrixRotationAxis(SBaseMatrix<T> *pOut, const SBaseVector3<T> *pV, T Angle)
{
    //����DX9�е����Ǻ��������Ż�,����ھ����Ͽ��ܲ���⺯����һ��
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

//3D������չ��4D��W��1��䡣Ȼ����������
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

//3D������չ��4D��W��0��䡣Ȼ����������
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

//���ָ��������͸��ͶӰ��������3DͶӰ�任��
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

//������X����ת�ľ���
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

//������Y����ת�ľ���
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

//������Z����ת�ľ���
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

//����һ����λ����
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

//�������������
template <class T>
SBaseMatrix<T>* SMatrixInverse(SBaseMatrix<T> *pOut, T *pDeterminant, const SBaseMatrix<T> *pM)
{
    //TODO:�д�����-�޷��ж��Ƿ������
    //���û�����򷵻�nullptr

    int n = 4;
    int i, j, k, m = 2 * n;
    T mik, temp;
    T **a = new T*[n];

    for (i = 0; i<n; i++)
    {
        a[i] = new T[2 * n];
    }

    //��ʼ��B=E
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
            a[i][j] = pM->m[i*n+j];           //����A��a������ı�A��ֵ

    for (i = 0; i<n; i++)
        for (j = n; j<m; j++)
            a[i][j] = pOut->m[i*n + j - n];  //����B��a���������

    //˳���˹��ȥ�������½�Ϊ��
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

    //��һ��
    for (i = 1; i <= n; i++)
    {
        temp = a[i - 1][i - 1];
        for (j = 1; j <= m; j++)
        {
            a[i - 1][j - 1] /= temp;
        }
    }

    //�����˹��ȥ��������������Ϊ��λ����
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
            pOut->m[i*n + j] = a[i][j + n];  //ȡ��������

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

//��������ת�þ���
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

//����һ������X,Y��Z�᷽�����ž���
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

// ����һ������X,Y��Z�᷽��ƽ�ƾ���
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

//����һ���任���������������ΪNULL���͵�����λ������
template <class T>
SBaseMatrix<T> *SMatrixTransformation(
    SBaseMatrix<T>				*pOut,
    const SBaseVector3<T>		*pScalingCenter,	//�ṹ�����������������������ΪNULL��Msc ����Ϊ��λ����
    const SBaseQuaternion<T>	*pScalingRotation,	//ָ��������תϵ����
    const SBaseVector3<T>		*pScaling,			//�����������������ΪNULL��Ms����Ϊ��λ����
    const SBaseVector3<T>		*pRotationCenter,	//��ת�������������ΪNULL��Mrc����Ϊ��λ����
    const SBaseQuaternion<T>	*pRotation,			//��ת�Ƕȡ�
    const SBaseVector3<T>		*pTranslation		//ƽ���������������ΪNULL��Mt����Ϊ��λ����
    )
{
    //�������������Ĺ�ʽ����任����
    //    Mout = (Msc)-1 * (Msr)-1 * Ms * Msr * Msc * (Mrc)-1 * Mr * Mrc * Mt
    //���� :
    //    Mout = �������(pOut)
    //    Msc = �������ľ���(pScalingCenter)
    //    Msr = ������ת����(pScalingRotation)
    //    Ms = ���ž���(pScaling)
    //    Mrc = ��ת���������(pRotationCenter)
    //    Mr = ��ת����(Rotation)
    //    Mt = ƽ�ƾ���(pTranslation)
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
    //TODO:������תϵ��ʲô��
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

//����һ������任�任����NULL�Ĳ����ͻᵱ���ǵ�λ����
template <class T>
SBaseMatrix<T> *SMatrixAffineTransformation(
    SBaseMatrix<T>				*pOut,				//���ؽ���ľ���	
    float						Scaling,			//����ϵ����
    const SBaseVector3<T>		*pRotationCenter,	//��ת�����������������ΪNULL������һ����λ�������Mrc ��
    const SBaseQuaternion<T>	*pRotation,			//��ת�����������ΪNULL�����õ�λ����Mr ���档
    const SBaseVector3<T>		*pTranslation		//�任���������ΪNULL�����õ�λ����Mt ��
    )
{

    //TODO::

    return pOut;
}
#endif