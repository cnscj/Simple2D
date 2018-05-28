#ifndef _SXBASEPOINT3_H_
#define _SXBASEPOINT3_H_
template <class T=float>
class SBasePoint3
{
public:

	SBasePoint3(T x=0, T y=0, T z=0)
        :x(x), y(y), z(z)
	{

	}
	SBasePoint3(const SBasePoint3 &pt)
	{
		this->x = pt.x;
		this->y = pt.y;
		this->z = pt.z;
	}
	/* 运算操作 */
	//取得距离
	double Distance(const SBasePoint3 &pt)
	{
		return sqrt((this->x - pt.x)*(this->x - pt.x) + (this->y - pt.y)*(this->y - pt.y) + (this->z - pt.z)*(this->z - pt.z));
	}
	//比较
	bool Equals(const SBasePoint3 &pt)
	{
		if (pt.x == this->x &&
			pt.y == this->y &&
			pt.z == this->z
			)return true;
		return false;
	}

	//属性操作
	T GetPointX(){ return this->x; }
	T GetPointY(){ return this->y; }
	T GetPointZ(){ return this->z; }
	//设置坐标
	void SetPoint(T x, T y ,T z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	//移动坐标
	void MovePoint(T x, T y ,T z)
	{
		this->x += x;
		this->y += y;
		this->z += z;
	}
	SBasePoint3  &operator  -()
	{
		this->x = -this->x;
		this->y = -this->y;
		this->y = -this->z;
		return *this;
	}
	SBasePoint3  &operator  +()
	{
		this->x = +this->x;
		this->y = +this->y;
		this->y = +this->z;
		return *this;
	}

	//定义赋值运算符＝
    bool operator ==(const SBasePoint3 &pt)const
	{
		if (pt.x == this->x &&
			pt.y == this->y &&
			pt.z == this->z
			)return true;
		return false;
	}
	SBasePoint3  &operator   =(const SBasePoint3 &pt)
	{
		this->x = pt.x;
		this->y = pt.y;
		this->z = pt.z;
		return *this;

	}
    SBasePoint3  operator	+(const SBasePoint3 &pt)const
	{
		SBasePoint3 t;
		t.x = pt.x + this->x;
		t.y = pt.y + this->y;
		t.z = pt.z + this->z;
		return t;
	}

	//点减法运算结果应为向量
    SBasePoint3  operator	-(const SBasePoint3 &pt)const
	{
		SBasePoint3 t;
		t.x = pt.x - this->x;
		t.y = pt.y - this->y;
		t.z = pt.z - this->z;
		return t;
	}

	SBasePoint3  &operator	+=(const SBasePoint3 &pt)
	{
		this->x += pt.x;
		this->y += pt.y;
		this->z += pt.z;
		return *this;
	}
	//定义减法运算符-
	SBasePoint3  &operator	-=(const SBasePoint3 &pt)
	{
		this->x -= pt.x;
		this->y -= pt.y;
		this->z -= pt.z;
		return *this;
	}

	//乘法
    SBasePoint3  operator	*(const double k)const
	{
		SBasePoint3 t;
		t.x = this->x * k;
		t.y = this->y * k;
		t.z = this->z * k;
		return t;
	}
	SBasePoint3  &operator	*=(const double k)
	{
		this->x *= k;
		this->y *= k;
		this->z *= k;
		return *this;
	}
	//除法
    SBasePoint3  operator	/(const double k)const
	{
		SBasePoint3 t;
		t.x = this->x / k;
		t.y = this->y / k;
		t.z = this->z / k;
		return t;
	}
	SBasePoint3  &operator	/=(const double k)
	{
		this->x /= k;
		this->y /= k;
		this->z /= k;
		return *this;
	}
public:
	T x;
	T y;
	T z;
};
#endif