#ifndef _SXBASEPOINT2_H_
#define _SXBASEPOINT2_H_
#include <math.h>
#include "SBaseRect.hpp"

template <class T = int>
class SBasePoint2
{
public:
    SBasePoint2(T x = 0, T y = 0);
    SBasePoint2(const SBasePoint2 &pt);
	/* 运算操作 */
	//取得距离
    double Distance(const SBasePoint2 &pt)const;
	//比较
    bool Equals(const SBasePoint2 &pt)const;

	//属性操作
    T GetX()const;
    T GetY()const;

	//设置坐标
    void SetPoint(T x, T y);
	//移动坐标
    void MovePoint(T x, T y);
    SBasePoint2  &operator  -();
    SBasePoint2  &operator  +();

	//定义赋值运算符＝
    bool operator ==(const SBasePoint2 &pt)const;
    SBasePoint2  &operator =(const SBasePoint2 &pt);
    SBasePoint2  operator	+(const SBasePoint2 &pt)const;

	//点减法运算结果应为向量
    SBasePoint2  operator	-(const SBasePoint2 &pt)const;
    SBasePoint2  &operator	+=(const SBasePoint2 &pt);
	//定义减法运算符-
    SBasePoint2  &operator	-=(const SBasePoint2 &pt);
	//乘法
    SBasePoint2  operator	*(const double k)const;
    SBasePoint2  &operator	*=(const double k);
	//除法
    SBasePoint2  operator	/(const double k)const;
    SBasePoint2  &operator	/=(const double k);

    //是否与矩形碰撞
    bool IsCollsion(const SBasePoint2 &pt);
    bool IsCollsion(const SBaseRect<T> &rt);
    //是否在矩形内
    bool IsInRect(const SBaseRect<T> &rt);
    //在矩形上
    bool IsOnRect(const SBaseRect<T> &rt);
public:
	T x;
	T y;
};

template <class T>
SBasePoint2<T>::SBasePoint2(T x, T y)
:x(x), y(y)
{

}

template <class T>
SBasePoint2<T>::SBasePoint2(const SBasePoint2 &pt)
{
    this->x = pt.x;
    this->y = pt.y;
}
/* 运算操作 */
//取得距离
template <class T>
double SBasePoint2<T>::Distance(const SBasePoint2 &pt)const
{
    return sqrt((this->x - pt.x)*(this->x - pt.x) + (this->y - pt.y)*(this->y - pt.y));
}
//比较
template <class T>
bool SBasePoint2<T>::Equals(const SBasePoint2 &pt)const
{
    if (pt.x == this->x &&
        pt.y == this->y
        )return true;
    return false;
}

//属性操作
template <class T>
T SBasePoint2<T>::GetX()const{ return this->x; }
template <class T>
T SBasePoint2<T>::GetY()const{ return this->y; }

//设置坐标
template <class T>
void SBasePoint2<T>::SetPoint(T x, T y)
{
    this->x = x;
    this->y = y;
}
//移动坐标
template <class T>
void SBasePoint2<T>::MovePoint(T x, T y)
{
    this->x += x;
    this->y += y;
}
template <class T>
SBasePoint2<T>  &SBasePoint2<T>::operator  -()
{
    this->x = -this->x;
    this->y = -this->y;
    return *this;
}
template <class T>
SBasePoint2<T>  &SBasePoint2<T>::operator  +()
{
    this->x = +this->x;
    this->y = +this->y;
    return *this;
}

//定义赋值运算符＝
template <class T>
bool SBasePoint2<T>::operator ==(const SBasePoint2 &pt)const
{
    if (pt.x == this->x &&
        pt.y == this->y
        )return true;
    return false;
}
template <class T>
SBasePoint2<T>  &SBasePoint2<T>::operator   =(const SBasePoint2 &pt)
{
    this->x = pt.x;
    this->y = pt.y;
    return *this;

}
template <class T>
SBasePoint2<T>  SBasePoint2<T>::operator	+(const SBasePoint2 &pt)const
{
    SBasePoint2<T> t;
    t.x = pt.x + this->x;
    t.y = pt.y + this->y;
    return t;
}

//点减法运算结果应为向量
template <class T>
SBasePoint2<T>  SBasePoint2<T>::operator	-(const SBasePoint2 &pt)const
{
    SBasePoint2<T> t;
    t.x = pt.x - this->x;
    t.y = pt.y - this->y;
    return t;
}

template <class T>
SBasePoint2<T>  &SBasePoint2<T>::operator	+=(const SBasePoint2 &pt)
{
    this->x += pt.x;
    this->y += pt.y;
    return *this;
}
//定义减法运算符-
template <class T>
SBasePoint2<T>  &SBasePoint2<T>::operator	-=(const SBasePoint2 &pt)
{
    this->x -= pt.x;
    this->y -= pt.y;
    return *this;
}

//乘法
template <class T>
SBasePoint2<T>  SBasePoint2<T>::operator	*(const double k)const
{
    SBasePoint2<T> t;
    t.x = this->x * k;
    t.y = this->y * k;
    return t;
}
template <class T>
SBasePoint2<T>  &SBasePoint2<T>::operator	*=(const double k)
{
    this->x *= k;
    this->y *= k;
    return *this;
}
//除法
template <class T>
SBasePoint2<T>  SBasePoint2<T>::operator	/(const double k)const
{
    SBasePoint2<T> t;
    t.x = this->x / k;
    t.y = this->y / k;
    return t;
}
template <class T>
SBasePoint2<T>  &SBasePoint2<T>::operator	/=(const double k)
{
    this->x /= k;
    this->y /= k;
    return *this;
}

//是否与矩形碰撞
template <class T>
bool SBasePoint2<T>::IsCollsion(const SBasePoint2 &pt)
{
    if (this->x == pt.x && this->y == pt.y)
        return true;
    else return false;
}

template <class T>
bool SBasePoint2<T>::IsCollsion(const SBaseRect<T> &rt)
{
    if (this->x >= rt.left && this->x <= rt.right && this->y >= rt.top && this->y <= rt.bottom) {
        return true;
    }
    return false;
}
//是否在矩形内
template <class T>
bool SBasePoint2<T>::IsInRect(const SBaseRect<T> &rt)
{
    if (this->x > rt.left &&this->x < rt.right
        && this->y > rt.top && this->y < rt.bottom)
        return true;
    else
        return false;
}
//在矩形上
template <class T>
bool SBasePoint2<T>::IsOnRect(const SBaseRect<T> &rt)
{
    if (this->x == rt.left || this->x == rt.right)
    {
        if (this->y >= rt.top && this->y <= rt.bottom)
            return true;
        return false;
    }
    if (this->y == rt.top || this->y == rt.bottom)
    {
        if (this->x >= rt.left && this->x <= rt.right)
            return true;
        return false;
    }
    return false;
}
#endif