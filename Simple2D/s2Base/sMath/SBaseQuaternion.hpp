#ifndef _SXBASEQUATERNION_H_
#define _SXBASEQUATERNION_H_

template<class T = float>
class SBaseQuaternion
{
public:
	SBaseQuaternion() {}
	SBaseQuaternion(const T *qua)
	{
		this->x = qua[0]; this->y = qua[1]; this->z = qua[2]; this->w = qua[3];
	}
	SBaseQuaternion(T x, T y, T z, T w)
	{
		this->x = x; this->y = y; this->z = z; this->w = w;
	}

	// casting
	operator T* ()
	{
		return this;
	}
	operator const T* () const
	{
		return this;
	}

	// 运算符重载
	SBaseQuaternion& operator += (const SBaseQuaternion &qua)
	{
		this->x += qua.x;
		this->y += qua.y;
		this->z += qua.z;
		this->w += qua.w;
		return *this;
	}
	SBaseQuaternion& operator -= (const SBaseQuaternion &qua)
	{
		this->x -= qua.x;
		this->y -= qua.y;
		this->z -= qua.z;
		this->w -= qua.w;
		return *this;
	}
	SBaseQuaternion& operator *= (const SBaseQuaternion &qua)
	{
		this->x = (this->x*qua.x - this->y*qua.y - this->z*qua.z-this->w*qua.w);
		this->y = (this->x*qua.y + this->y*qua.x - this->z*qua.w - this->w*qua.z);
		this->z = (this->x*qua.z - this->y*qua.w + this->z*qua.x + this->w*qua.y);
		this->w = (this->x*qua.w + this->y*qua.x - this->z*qua.y + this->w*qua.z);

		return *this;
	}
	SBaseQuaternion& operator *= (T k)
	{
		this->x *= k;
		this->y *= k;
		this->z *= k;
		this->w *= k;
		return *this;
	}
	SBaseQuaternion& operator /= (T k)
	{
		this->x /= k;
		this->y /= k;
		this->z /= k;
		this->w /= k;
		return *this;
	}

	// 一元运算重载,取正反数
	SBaseQuaternion  operator + () const
	{
		return SBaseQuaternion(+this->x, +this->y, +this->z, +this->w);
	}
	SBaseQuaternion  operator - () const
	{
		return SBaseQuaternion(-this->x, -this->y, -this->z, -this->w);
	}

	// binary operators
	SBaseQuaternion operator + (const SBaseQuaternion &qua) const
	{
		return SBaseQuaternion(this->x + qua.x, this->y + qua.y, this->z + qua.z, this->w + qua.w);
	}
	SBaseQuaternion operator - (const SBaseQuaternion &qua) const
	{
		return SBaseQuaternion(this->x - qua.x, this->y - qua.y, this->z - qua.z, this->w - qua.w);
	}
	SBaseQuaternion operator * (const SBaseQuaternion &qua) const
	{
		SBaseQuaternion t(*this);
		t *= qua;
		return t;
	}
	SBaseQuaternion operator * (double k) const
	{
		return SBaseQuaternion(this->x * k, this->y * k, this->z * k, this->w * k);
	}
	SBaseQuaternion operator / (double k) const
	{
		return SBaseQuaternion(this->x / k, this->y / k, this->z / k, this->w / k);
	}

	friend SBaseQuaternion operator * (double k, const SBaseQuaternion &qua);

	bool operator == (const SBaseQuaternion &qua) const
	{
		if (this->x == qua.x &&
			this->y == qua.y &&
			this->z == qua.z &&
			this->w == qua.w 
			) return true;
		return false;
	}
	bool operator != (const SBaseQuaternion &qua) const
	{
		if (this->x != qua.x ||
			this->y != qua.y ||
			this->z != qua.z ||
			this->w != qua.w
			) return true;
		return false;
	}

public:
	T x, y, z, w;
};

#endif