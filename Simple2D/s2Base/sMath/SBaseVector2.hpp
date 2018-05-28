#ifndef _SXBASEVECTOR2_H_
#define _SXBASEVECTOR2_H_
#include <math.h>
template<class T = float>
class SBaseVector2
{
public:
	SBaseVector2<T>(T ix=0, T iy=0)
	:x(ix),y(iy)
	{

	}
	SBaseVector2<T>(T arr[2])
	{
		x = arr[0];
		y = arr[1];
	}
	inline SBaseVector2<T>& operator=(const SBaseVector2<T> &vec)
	{
		x = vec.x;
		y = vec.y;
		return *this;
	}
	inline SBaseVector2<T> operator+(const SBaseVector2<T> &vec)const
	{
		return SBaseVector2<T>(x + vec.x, y + vec.y);
	}
	inline SBaseVector2<T> &operator+=(const SBaseVector2<T> &vec)
	{
		x += vec.x; y += vec.y;
		return *this;
	}
	inline SBaseVector2<T> operator-(const SBaseVector2<T> &vec)const
	{
		return SBaseVector2<T>(x - vec.x, y - vec.y);
	}

	inline SBaseVector2<T> &operator-=(const SBaseVector2<T> &vec)
	{
		x -= vec.x; y -= vec.y;
		return *this;
	}

	inline SBaseVector2<T> operator/(const T s)const
	{
		return SBaseVector2<T>(x / s, y / s);
	}

	inline SBaseVector2<T> &operator/=(const T s)
	{
		x /= s; y /= s;
		return *this;
	}

	inline SBaseVector2<T> operator*(const T s)const
	{
		return SBaseVector2<T>(x * s, y * s);
	}

	inline SBaseVector2<T> &operator*=(const T s)
	{
		x *= s; y *= s;
		return *this;
	}

	inline double Magnitude() const
	{
		return sqrt(x*x + y*y);
	}
	inline double Length()const
	{
		return Magnitude();
	}

	inline SBaseVector2<T> &Normalize()
	{
		T Length = sqrt(x*v.x + v.y*v.y); //向量长度;  
		x /= Length;
		y /= Length; 
		return *this;
	}

    inline T Dot(const SBaseVector2<T> &v)
    {
        return (x*v.x + y*v.y);
    }
    inline double Angle(const SBaseVector2<T> &v)
    {
        return acos(Dot(v) /(Magnitude() * v.Magnitude()));
    }
    inline SBaseVector2<T> Cross(const SBaseVector2<T> &v)
    {
        return SBaseVector2<T>(0, 0);
    }

	//friend SBaseVector2<T> operator*(const T &s, const SBaseVector2<T> &vec)
	//{
	//	return SBaseVector2<T>(s*vec.x, s*vec.y);
	//}
	//friend SBaseVector2<T> operator/(const T &s, const SBaseVector2<T> &vec)
	//{
	//	return SBaseVector2<T>(vec.x / s, vec.y / s);
	//}


	T x;
	T y;
};

#endif