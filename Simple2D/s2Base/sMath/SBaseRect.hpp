/**
* SBaseRect结构体
* 矩形
* @author ZeroX
* @version v1.0 03/09/2017
*/
#ifndef _SXBASERECT_H_
#define _SXBASERECT_H_

//#include "SBasePoint2.hpp"
//#include "SBaseSize.hpp"

template<class T = int>
class SBaseRect
{
public:
    SBaseRect(const SBaseRect &rt);
	SBaseRect(T left=0,T top=0,T right=0,T bottom=0);

    T GetX()const;
    T GetY()const;
    //SBasePoint2<T> GetPosition() const;
    T GetWidth()const;
    T GetHeight()const;
    //SBaseSize<T> GetSize()const;
	//取得面积
    T GetArea()const;
	//取得周长
    T GetPerimeter()const;
	//取得几何中心
    //SBasePoint2<T> GetCenter()const;
	//按向量移动矩形
	void Move(T x, T y);
    //设为空
    void Empty();
	//移动到指定矩形的中心
    void MoveToCenter(const SBaseRect &rt);
	//矩形是否碰撞
    bool IsCollision(const SBaseRect &rt)const;
    bool IsCollision(const SBaseRect &rt, SBaseRect *out)const;

	//是否在矩形内
    bool IsInRect(const SBaseRect &rt)const;

    bool operator ==(const SBaseRect &rt)const;
    bool operator >(const SBaseRect &rt)const;
    SBaseRect &operator =(const SBaseRect &rt);
public:
    T left, top, right, bottom;
};

template<class T>
SBaseRect<T>::SBaseRect(const SBaseRect &rt)
{
    this->left = rt.left;
    this->right = rt.right;
    this->top = rt.top;
    this->bottom = rt.bottom;
}
template<class T>
SBaseRect<T>::SBaseRect(T left, T top, T right, T bottom)
:left(left), top(top), right(right), bottom(bottom)
{

}
template<class T>
T SBaseRect<T>::GetX()const
{
    return left;
}
template<class T>
T SBaseRect<T>::GetY()const
{
    return top;
}
//template<class T>
//SBasePoint2<T> SBaseRect<T>::GetPosition() const
//{
//    return SBasePoint2<T>(left, top);
//}
template<class T>
T SBaseRect<T>::GetWidth()const
{
    return right - left;
}
template<class T>
T SBaseRect<T>::GetHeight()const
{
    return bottom - top;
}
//template<class T>
//SBaseSize<T> SBaseRect<T>::GetSize()const
//{
//    return SBaseSize<T>(GetWidth(), GetHeight());
//}
//取得面积
template<class T>
T SBaseRect<T>::GetArea()const
{
    return (GetWidth() * GetHeight());
}
//取得周长
template<class T>
T SBaseRect<T>::GetPerimeter()const
{
    return (2 * (GetWidth() + GetHeight()));
}

//取得几何中心
//template<class T>
//SBasePoint2<T> SBaseRect<T>::GetCenter()const
//{
//    SBasePoint2<T> pt;
//    pt.x = (this->right - this->left) / 2;
//    pt.y = (this->bottom - this->top) / 2;
//    return pt;
//}

//按向量移动矩形
template<class T>
void SBaseRect<T>::Move(T x, T y)
{
    this->left += x;
    this->right += x;
    this->top += y;
    this->bottom += y;
}
template<class T>
void SBaseRect<T>::Empty()
{
    this->left = 0;
    this->right = 0;
    this->top = 0;
    this->bottom = 0;
}

//移动到指定矩形的中心
template<class T>
void SBaseRect<T>::MoveToCenter(const SBaseRect &rt)
{
    //取得rt中心点和对象中点
    int rtCenterX = (rt.right - rt.left) / 2;
    int rtCenterY = (rt.bottom - rt.top) / 2;
    int objCenterX = (this->right - this->left) / 2;
    int objCenterY = (this->bottom - this->top) / 2;

    //求出位移向量
    int disX = rtCenterX - objCenterX;
    int disY = rtCenterY - objCenterY;

    //让对象中心点与如图中心点重合
    Move(disX, disY);

}
template<class T>
bool SBaseRect<T>::IsCollision(const SBaseRect &rt)const
{
    auto rt1 = this;
    auto rt2 = &rt;

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

template<class T>
bool SBaseRect<T>::IsCollision(const SBaseRect &rt, SBaseRect *out) const
{
    SBaseRect<T> *lpDstRect = &out;
    const SBaseRect<T> *lpSrcRect1 = this;
    const SBaseRect<T> *lpSrcRect2 = &rt;

    if (lpSrcRect1->left>lpSrcRect2->left)
    {
        lpDstRect->left = lpSrcRect1->left;
    }
    else
    {
        lpDstRect->left = lpSrcRect2->left;
    }

    if (lpSrcRect1->top>lpSrcRect2->top)
    {
        lpDstRect->top = lpSrcRect1->top;
    }
    else
    {
        lpDstRect->top = lpSrcRect2->top;
    }

    if (lpSrcRect1->right>lpSrcRect2->right)
    {
        lpDstRect->right = lpSrcRect2->right;
    }
    else
    {
        lpDstRect->right = lpSrcRect1->right;
    }

    if (lpSrcRect1->bottom>lpSrcRect2->bottom)
    {
        lpDstRect->bottom = lpSrcRect2->bottom;
    }
    else
    {
        lpDstRect->bottom = lpSrcRect1->bottom;
    }
    if (lpDstRect->left >= lpDstRect->right || lpDstRect->top >= lpDstRect->bottom)
    {
        lpDstRect->Empty();
        return false;
    }
    else
    {
        return true;
    }
    return true;
}

template<class T>
bool SBaseRect<T>::IsInRect(const SBaseRect &rt)const
{
    if (((left >= rt.left) && (right <= rt.right)) && ((top >= rt.top) && (bottom <= rt.bottom)))
        return true;
    else
        return false;
}
template<class T>
bool SBaseRect<T>::operator ==(const SBaseRect &rt)const
{
    if (this->left == rt.left &&
        this->right == rt.right &&
        this->top == rt.top &&
        this->bottom == rt.bottom
        ) return true;
    else return false;
}
template<class T>
bool SBaseRect<T>::operator >(const SBaseRect &rt)const
{
    return this->GetArea() > rt.GetArea();
}

template<class T>
SBaseRect<T> &SBaseRect<T>::operator =(const SBaseRect &rt)
{
    this->left = rt.left;
    this->right = rt.right;
    this->top = rt.top;
    this->bottom = rt.bottom;
    return *this;
}
#endif