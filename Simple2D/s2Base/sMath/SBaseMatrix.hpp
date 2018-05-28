#ifndef _SXBASEMATRIX_H_
#define _SXBASEMATRIX_H_
#include <math.h>
#include "SBaseVector4.hpp"
#include "SBaseVector3.hpp"

template <class T = float>
class SBaseMatrix
{
public:
	SBaseMatrix<T>();
	SBaseMatrix<T>(const SBaseMatrix<T> &mat);
	SBaseMatrix<T>(T m0,T m1,T m2,T m3,
			   T m4,T m5,T m6,T m7,
			   T m8,T m9,T m10,T m11,
			   T m12,T m13,T m14,T m15);
	SBaseMatrix<T>(T arr[16]);
	inline void SetIdentity();
	inline void SetInverse();
	inline void SetValue(T m0,T m1,T m2,T m3,
			   T m4,T m5,T m6,T m7,
			   T m8,T m9,T m10,T m11,
			   T m12,T m13,T m14,T m15);

	inline void DisplayValue();
	inline void SetTranspose();

	inline SBaseMatrix<T> &operator=(const SBaseMatrix<T> &mat);
	inline SBaseMatrix<T> operator*(const SBaseMatrix<T> &mat) const;
	inline bool operator==(const SBaseMatrix<T> &mat)const;
	inline bool operator!=(const SBaseMatrix<T> &mat)const;
	inline SBaseMatrix<T> operator+(const SBaseMatrix<T> &mat)const;
	inline SBaseMatrix<T> operator-(const SBaseMatrix<T> &mat)const;
    inline T &operator[](int index)const;
	inline void SetTranslation(const SBaseVector3<T> &vec);
	inline void SetRotate(float angle,float x,float y,float z);
	inline void SetScale(T x, T y, T z);
public:
    //FIXME:存在16K对齐问题
	/*__declspec(align(16))*/ T m[16];
	T &_11 = m[0]; T &_12 = m[1]; T &_13 = m[2]; T &_14 = m[3];
	T &_21 = m[4]; T &_22 = m[5]; T &_23 = m[6]; T &_24 = m[7];
	T &_31 = m[8]; T &_32 = m[9]; T &_33 = m[10]; T &_34 = m[11];
	T &_41 = m[12]; T &_42 = m[13]; T &_43 = m[14]; T &_44 = m[15];
	//the friend funciton is not the member function of the SBaseMatrix, but the have friend declare
	//so the function can access the private member of the Class Mattix4
	friend SBaseVector4<T> 
				  operator*(const SBaseVector4<T> &vec,const SBaseMatrix<T> &mat)
	{
		return SBaseVector4<T>(vec.x*mat.m[0] + vec.y *mat.m[1] + vec.z *mat.m[2] + vec.w *mat.m[3],
						  vec.x*mat.m[4] + vec.y *mat.m[5] + vec.z *mat.m[6] + vec.w *mat.m[7],
						  vec.x*mat.m[8] + vec.y *mat.m[9] + vec.z *mat.m[10] + vec.w *mat.m[11],
						  vec.x*mat.m[12] + vec.y *mat.m[13] + vec.z *mat.m[14] + vec.w *mat.m[15]);
	}
	friend SBaseVector4<T> 
				  operator*(const SBaseMatrix<T> &mat,const SBaseVector4<T> &vec)
	{
		return SBaseVector4<T>(vec.x*mat.m[0] + vec.y *mat.m[4] + vec.z *mat.m[8] + vec.w *mat.m[12],
						  vec.x*mat.m[1] + vec.y *mat.m[5] + vec.z *mat.m[9] + vec.w *mat.m[13],
						  vec.x*mat.m[2] + vec.y *mat.m[6] + vec.z *mat.m[10] + vec.w *mat.m[14],
						  vec.x*mat.m[3] + vec.y *mat.m[7] + vec.z *mat.m[11] + vec.w *mat.m[15]);
	}
	
	friend SBaseMatrix<T>
				  operator*(const T &s, const SBaseMatrix<T> &mat)
	{
		SBaseMatrix<T> ret;
		for( int i = 0; i < 16; i++)
			ret.m[i] = s * (mat.m[i]);
		return ret;
	}
};

template<class T>
inline SBaseMatrix<T>::SBaseMatrix()
{
	SetIdentity();
}
template<class T>
inline SBaseMatrix<T>::SBaseMatrix(const SBaseMatrix<T> &mat)
{
	*this = mat;
}
template<class T>
inline SBaseMatrix<T>::SBaseMatrix(T m0, T m1, T m2, T m3, 
						T m4, T m5, T m6, T m7, 
						T m8, T m9, T m10, T m11, 
						T m12, T m13, T m14, T m15)
{
	m[0] = m0;m[1] = m1;m[2] = m2;m[3] = m3;
	m[4] = m4;m[5] = m5;m[6] = m6;m[7] = m7;
	m[8] = m8;m[9] = m9;m[10] = m10;m[11] = m11;
	m[12] = m12;m[13] = m13;m[14] = m14;m[15] = m15;
}

template<class T>
inline SBaseMatrix<T>::SBaseMatrix(T arr[16])
{
	for(int i = 0; i < 16; i++)
	{
		m[i] = arr[i];
	}
}

template<class T>
inline void SBaseMatrix<T>::SetIdentity()
{
	for(int i = 0; i < 16; i++)
	{
		m[i] = 0;
	}
	m[0] = 1; m[5]=1;
	m[10] = 1; m[15] =1;
}
template<class T>
inline void SBaseMatrix<T>::DisplayValue()
{
	for( int i = 0 ; i< 4; i++)
	{
		cout<<m[i]<<" "<<m[i+4]<<" "<<m[i+8]<<" "<<m[i+12]<<endl;
	}
}
template<class T>
inline SBaseMatrix<T>& SBaseMatrix<T>::operator =(const SBaseMatrix<T> &mat)
{
	memcpy(m,mat.m,sizeof(T)*16);
	return *this;
}
template<class T> 
inline bool SBaseMatrix<T>::operator==(const SBaseMatrix<T> &mat)const
{
	int i=0;
	while( m[i++] == mat.m[i++] )
	{
		if(i==16) break;
	};
	return (i==16)?true:false;
}
template<class T>
inline bool SBaseMatrix<T>::operator!=(const SBaseMatrix<T> &mat)const
{
	int i=0;
	while( m[i++] == mat.m[i++] )
	{
		if(i==16) break;
	};
	return (i==16)?false:true;
}
template<class T>
inline void SBaseMatrix<T>::SetValue(T m0, T m1, T m2, T m3, 
								 T m4, T m5, T m6, T m7, 
								 T m8, T m9, T m10, T m11,
								 T m12, T m13, T m14, T m15)
{
	m[0] = m0;m[1] = m1;m[2] = m2;m[3] = m3;
	m[4] = m4;m[5] = m5;m[6] = m6;m[7] = m7;
	m[8] = m8;m[9] = m9;m[10] = m10;m[11] = m11;
	m[12] = m12;m[13] = m13;m[14] = m14;m[15] = m15;
}

template<class T>
inline SBaseMatrix<T> SBaseMatrix<T>::operator+(const SBaseMatrix<T> &mat)const
{
	return SBaseMatrix<T>(m[0]+mat.m[0],m[1]+mat.m[1],m[2]+mat.m[2],m[3]+mat.m[3],
					  m[4]+mat.m[4],m[5]+mat.m[5],m[6]+mat.m[6],m[7]+mat.m[7],
					  m[8]+mat.m[8],m[9]+mat.m[9],m[10]+mat.m[10],m[11]+mat.m[11],
					  m[12]+mat.m[12],m[13]+mat.m[13],m[14]+mat.m[14],m[15]+mat.m[15]);
}
template<class T>
inline SBaseMatrix<T> SBaseMatrix<T>::operator-(const SBaseMatrix<T> &mat)const
{
	return SBaseMatrix<T>(m[0]-mat.m[0],m[1]-mat.m[1],m[2]-mat.m[2],m[3]-mat.m[3],
					  m[4]-mat.m[4],m[5]-mat.m[5],m[6]-mat.m[6],m[7]-mat.m[7],
					  m[8]-mat.m[8],m[9]-mat.m[9],m[10]-mat.m[10],m[11]-mat.m[11],
					  m[12]-mat.m[12],m[13]-mat.m[13],m[14]-mat.m[14],m[15]-mat.m[15]);
}

template<class T>
inline void SBaseMatrix<T>::SetInverse()
{
	T src[16];
	for(int i = 0; i< 16; i++)
	{
		src[i] = m[i];
	}
	this->SetIdentity();
	
	for(int i=0; i<4; i++)
	{
		int curr = i; //当前处理的行号
		int col = i+1; //需要消除的初行
		int j = i*5; //对角元素脚标

		/*cout <<"------------------"<<endl;
		cout << "this is time:"<< i<<endl;*/

		//find the max of the i column
		int max=j;
		for(int k = j+1; k<j+4-i; k++)
		{
			if(abs(src[k])> abs(src[max])) max = k;
		}

		//cout<<"the current max sub is "<<max<<" "<<src[max]<<endl;

		//由对角元素脚标取得列号
		max = max%4; 
		//cout<<"the max row is "<<max<<endl;
		
		//inter the max row and i row
		if( max != i)
		{
			for ( int k = 0,p=i; k< 4; k++)
			{
				T temp1 = src[p];
				src[p] = src[max];
				src[max] = temp1;

				//对应单位矩阵变换
				T temp2 = m[p];
				m[p] = m[max];
				m[max] = temp2;

				p+=4;
				max+=4;
			}
		}

		T tempMax=src[j]; //除以对角元素化为1
		for( int k=0;k<4;k++)
		{
			src[curr]=src[curr]/tempMax;
			m[curr] = m[curr]/tempMax;
			curr+=4;
		}


		//消除i-> 3行对应元素为0
		int r = j+1;
		for(int k = 0; k <3-i; k++)
		{
			r = j+k+1;
			T temp = -src[r];
			col = i+k+1;
			curr = i;
			//cout<<"deal with the col is "<<col<<endl;
			for(int n=0;n<4;n++)
			{
				src[col] = temp*src[curr] + src[col];
				m[col] = temp*m[curr]+m[col];
				curr+=4;
				col+=4;
			}
		}
	}

	for(int i=3; i>0; i--)
	{
		//cout<<"the begin right is " << i<<endl;
		int curr = i;
		int col = i-1;
		//需要处理i行
		for( int j=i-1;j>=0; j--)
		{
			int r = i*5-(i-j); 
			T temp = -src[r];//得到上三角对角元素该列的值
			col=j;
			curr=i;
			//cout<<"the col "<<col<<endl;
			for( int n=0;n<4;n++)
			{
				src[col] = temp * src[curr] + src[col];
				m[col] = temp * m[curr] + m[col];
				col+=4;
				curr+=4;
			}
		}
	}
}
template<class T>
inline void SBaseMatrix<T>::SetTranspose()
{
	T src[16];
	for(int i = 0; i < 16; i++)
	{
		src[i] = m[i];
	}
	SetIdentity();

	for( int i = 0,j = 0; i < 4; i++)
	{
		m[i] = src[j++];
		m[i+4] = src[j++];
		m[i+8] = src[j++];
		m[i+12] = src[j++];
	}
}
template <class T>
inline SBaseMatrix<T> SBaseMatrix<T>::operator *(const SBaseMatrix<T> &mat) const
{
	return SBaseMatrix<T>(
        mat.m[0] * m[0] + mat.m[4] * m[1] + mat.m[8] * m[2] + mat.m[12] * m[3],
        mat.m[1] * m[0] + mat.m[5] * m[1] + mat.m[9] * m[2] + mat.m[13] * m[3],
        mat.m[2] * m[0] + mat.m[6] * m[1] + mat.m[10] * m[2] + mat.m[14] * m[3],
        mat.m[3] * m[0] + mat.m[7] * m[1] + mat.m[11] * m[2] + mat.m[15] * m[3],
        mat.m[0] * m[4] + mat.m[4] * m[5] + mat.m[8] * m[6] + mat.m[12] * m[7],
        mat.m[1] * m[4] + mat.m[5] * m[5] + mat.m[9] * m[6] + mat.m[13] * m[7],
        mat.m[2] * m[4] + mat.m[6] * m[5] + mat.m[10] * m[6] + mat.m[14] * m[7],
        mat.m[3] * m[4] + mat.m[7] * m[5] + mat.m[11] * m[6] + mat.m[15] * m[7],
        mat.m[0] * m[8] + mat.m[4] * m[9] + mat.m[8] * m[10] + mat.m[12] * m[11],
        mat.m[1] * m[8] + mat.m[5] * m[9] + mat.m[9] * m[10] + mat.m[13] * m[11],
        mat.m[2] * m[8] + mat.m[6] * m[9] + mat.m[10] * m[10] + mat.m[14] * m[11],
        mat.m[3] * m[8] + mat.m[7] * m[9] + mat.m[11] * m[10] + mat.m[15] * m[11],
        mat.m[0] * m[12] + mat.m[4] * m[13] + mat.m[8] * m[14] + mat.m[12] * m[15],
        mat.m[1] * m[12] + mat.m[5] * m[13] + mat.m[9] * m[14] + mat.m[13] * m[15],
        mat.m[2] * m[12] + mat.m[6] * m[13] + mat.m[10] * m[14] + mat.m[14] * m[15],
        mat.m[3] * m[12] + mat.m[7] * m[13] + mat.m[11] * m[14] + mat.m[15] * m[15]
        );
}

template <class T>
inline void SBaseMatrix<T>::SetTranslation(const SBaseVector3<T> &vec)
{
	this->SetIdentity();
	this->m[12] = vec.x;
	this->m[13] = vec.y;
	this->m[14] = vec.z;
}
template<class T>
inline void SBaseMatrix<T>::SetRotate(float angle,float x,float y,float z)
{
	float axisVecLength = sqrt(x*x + y*y + z*z);
	float angleRadian = 3.1415926f * angle/180.0f;
	float cosA = cos(angleRadian);
	float oneC = 1 - cosA;
	float sinA = sin(angleRadian);

	float ux = x / axisVecLength;
	float uy = y / axisVecLength;
	float uz = z / axisVecLength;

	SBaseMatrix<T> matQuaternionRot;
	matQuaternionRot.SetIdentity();

	matQuaternionRot.m[0] = ux*ux*oneC + cosA;
	matQuaternionRot.m[4] = ux*uy*oneC - uz*sinA;
	matQuaternionRot.m[8] = ux*uz*oneC + uy*sinA;
	matQuaternionRot.m[1] = uy*ux*oneC + uz*sinA;
	matQuaternionRot.m[5] = uy*uy*oneC + cosA;
	matQuaternionRot.m[9] = uy*uz*oneC - ux*sinA;
	matQuaternionRot.m[2] = uz*ux*oneC - uy*sinA;
	matQuaternionRot.m[6] = uz*uy*oneC + uz*sinA;
	matQuaternionRot.m[10] = uz*uz*oneC + cosA;

	*this = matQuaternionRot * (*this);
}
template <class T>
inline void SBaseMatrix<T>::SetScale(T x, T y, T z)
{
	SBaseMatrix<T> scalMat(x,0,0,0,
					   0,y,0,0,
					   0,0,z,0,
					   0,0,0,1);
	*this = scalMat * (*this);
}

#endif _SXBASXMATRIX_H_
