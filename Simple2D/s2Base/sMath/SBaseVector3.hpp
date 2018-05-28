#ifndef _S2BASEVECTOR3_H_
#define _S2BASEVECTOR3_H_

template<class T = float>
class SBaseVector3
{
	public:
		SBaseVector3<T>(){}
		SBaseVector3<T>(T ix,T iy,T iz){
			x = ix;
			y = iy;
			z = iz;
		}
		SBaseVector3<T>(T arr[3])
		{
			x = arr[0];
			y = arr[1];
			z = arr[2];
		}
		inline SBaseVector3<T>& operator=(const SBaseVector3<T> &vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;
			return *this;
		}
		inline SBaseVector3<T> operator+(const SBaseVector3<T> &vec)const
		{
			return SBaseVector3<T>(x + vec.x,y + vec.y,z + vec.z);
		}
		inline SBaseVector3<T> &operator+=(const SBaseVector3<T> &vec)
		{
			x += vec.x; y += vec.y; z += vec.z;
			 return *this;
		}
		inline SBaseVector3<T> operator-(const SBaseVector3<T> &vec)const
		{
			return SBaseVector3<T>(x - vec.x,y - vec.y,z - vec.z);
		}

		inline SBaseVector3<T> &operator-=(const SBaseVector3<T> &vec)
		{
			x -= vec.x; y -= vec.y; z -= vec.z;
			return *this;
		}

		inline SBaseVector3<T> operator/(const T s)const
		{
			return SBaseVector3<T>(x / s, y / s, z / s);
		}

		inline SBaseVector3<T> &operator/=(const T s)
		{
			x /= s; y /= s; z /= s;
			return *this;
		}

		inline SBaseVector3<T> operator*(const T s)const
		{
			return SBaseVector3<T>(x * s, y * s, z * s);
		}

		inline SBaseVector3<T> &operator*=(const T s)
		{
			x *= s; y *= s; z *= s;
			return *this;
		}

		inline double Magnitude() const
		{
			return sqrt(x*x + y*y + z*z);
		}
		inline double Length()const
		{
			return Magnitude();
		}
		inline SBaseVector3<T> &Normalize()
		{
			double Length = sqrt(x*v.x + v.y*v.y + v.z*v.z); //向量长度;  
			x /= Length;
			y /= Length;
			z /= Length; //获取到规格化的向量;  
			return *this;
		}
        inline double Dot(const SBaseVector3<T> &v)
        {
            return (x*v.x + y*v.y + z*v.z);
        }
        inline double Angle(const SBaseVector3<T> &v)
        {
            return acos(Dot(v) /
                (Magnitude() * v.Magnitude()));
        }
        inline SBaseVector3<T> Cross(const SBaseVector3<T> &v)
        {
            return SBaseVector3<T>(
                y * v.z - z * v.y,
                z * v.x - x * v.z,
                x * v.y - y * v.x
                );
        }

	/*	friend SBaseVector3<T> operator*(const T &s, const SBaseVector3<T> &vec)
		{
			return SBaseVector3<T>(s*vec.x,s*vec.y,s*vec.z);
		}
		friend SBaseVector3<T> operator/(const T &s, const SBaseVector3<T> &vec)
		{
			return SBaseVector3<T>(vec.x / s, vec.y / s, vec.z / s);
		}*/
		
		T x;
		T y;
		T z;
};
#endif _SXBASXVECTOR3_H_
