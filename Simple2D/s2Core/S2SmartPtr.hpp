/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-19 22:30:06 
 * @Brief: 智能指针
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-19 22:36:05
 * @Last Modified log: 
 */
#ifndef _S2SMARTPTR_H_
#define _S2SMARTPTR_H_
#include "S2Object.h"
template <class T>
class S2SmartPtr;

// 智能指针对象
template <class T>
class S2SmartPtr : public S2Object
{
private:
    // 智能指针引用计数类
    class PtrInfo
    {
    public:
        PtrInfo(T* p);
        virtual ~PtrInfo();
    public:
        T* m_pTtr; // 实际的指针
        size_t m_RefCount; // 引用计数

    };
public:
	S2SmartPtr();
	S2SmartPtr(T* p);
	S2SmartPtr(S2SmartPtr<T>& other);// 拷贝构造函数,引用计数+1
	~S2SmartPtr();

	// 重载运算=,将左对象引用计数-1,并判断是否delete;将右对象+1;
	S2SmartPtr<T> & operator = (S2SmartPtr& other);
	// 重载指针操作*,->
	T& operator *();
	T* operator ->();

    size_t GetRefCount();	//取得引用次数
	T* GetRefPtr();		//取得引用指针
private:
    PtrInfo* m_pShread; // 引用计数
};

template <class T>
S2SmartPtr<T>::PtrInfo::PtrInfo(T* p)
{
    m_pTtr = p;
    m_RefCount = 1;
}

template <class T>
S2SmartPtr<T>::PtrInfo::~PtrInfo()
{
    if (m_pTtr)
    {
        delete m_pTtr;
        m_RefCount = 0;
    }
    m_pTtr = NULL;
}

////
template <class T>
S2SmartPtr<T>::S2SmartPtr()
{
	m_pShread = NULL;
}

template<class T>
S2SmartPtr<T>::S2SmartPtr(T* p)
{
	//为每一个新指针new一个
    m_pShread = new PtrInfo(p);
}

template <class T>
S2SmartPtr<T>::S2SmartPtr(S2SmartPtr<T>& other)
{
	this->m_pShread = other.m_pShread;
	++(m_pShread->m_RefCount);
}

template <class T>
S2SmartPtr<T>& S2SmartPtr<T>::operator=(S2SmartPtr& other)
{
	// 将右操作对象引用计数+1
	++(other.m_pShread->m_RefCount);

	// 由于左操作对象指向了新对象,需要将操作数-1;
	// 同时也防止了自赋值的方式.
	// 首先要判断这个对象是否已经指向了其他对象,这个很重要!防止左指针对象为null的情况.
	if (this->m_pShread)
	{
		if (--(this->m_pShread->m_RefCount) == 0)
		{
			delete this->m_pShread;
		}
	}

	this->m_pShread = other.m_pShread;
	return *this;
}

template <class T>
T& S2SmartPtr<T>::operator *()
{
	return *(m_pShread->m_pTtr);
}

template <class T>
T* S2SmartPtr<T>::operator->()
{
	return (m_pShread->m_pTtr);
}

template <class T>
S2SmartPtr<T>::~S2SmartPtr()
{
	if (m_pShread)
	{
		if ((--m_pShread->m_RefCount) == 0)
		{
			delete m_pShread;
			m_pShread = NULL;
		}
	}
}

template <class T>
size_t S2SmartPtr<T>::GetRefCount()
{
	if (m_pShread)
		return m_pShread->m_RefCount;
	return 0;
}
template <class T>
T* S2SmartPtr<T>::GetRefPtr()
{
	if (m_pShread)
		return (m_pShread->m_pTtr);
	return NULL;
}
#endif
