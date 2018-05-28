#ifndef _S2BASEVECTOR4_H_
#define _S2BASEVECTOR4_H_

template<class T = float>
class SBaseVector4
{
	public:
		SBaseVector4<T>(){}
		SBaseVector4<T>(T ix,T iy,T iz, T iw){
			x = ix;
			y = iy;
			z = iz;
			w = iw;
		}
		SBaseVector4<T>(T arr[4])
		{
			x = arr[0];
			y = arr[1];
			z = arr[2];
			w = arr[3];
		}
		inline SBaseVector4<T>& operator=(const SBaseVector4<T> &vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;
			w = vec.w;
			return *this;
		}
		inline SBaseVector4<T> operator+(const SBaseVector4<T> &vec)const
		{
			return SBaseVector4<T>(x + vec.x,y + vec.y,z + vec.z,w + vec.w);
		}
		inline SBaseVector4<T> operator-(const SBaseVector4<T> &vec)const
		{
			return SBaseVector4<T>(x - vec.x,y - vec.y,z - vec.z,w - vec.w);
		}
		friend SBaseVector4<T> operator*(const T &s, const SBaseVector4<T> &vec)
		{
			return SBaseVector4<T>(s*vec.x,s*vec.y,s*vec.z,s*vec.w);
		}
		
		T x;
		T y;
		T z;
		T w;
		
};
#endif _SXBASXVECTOR4_H_
