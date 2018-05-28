/**
* SSharedPtr��
* @brief ����ָ��-����ָ��
* @details ����ָ��,ʵ�������Զ�����
* @author inzaghihalo
* @link http://blog.csdn.net/superinzaghi747/article/details/52638709
* @version v1.0
* @date 2016-09-23
* @update 2017-09-25
*/

#ifndef _SSHAREDPTR_H
#define _SSHAREDPTR_H
#include "SReference.h"
template <class T>
class SSharedPtr;

// ����ָ�����
template <class T>
class SSharedPtr : public SReference
{
private:
    // ����ָ�����ü�����
    class PtrInfo
    {
    public:
        PtrInfo(T* p);
        virtual ~PtrInfo();
    public:
        T* m_pTtr; // ʵ�ʵ�ָ��
        size_t m_RefCount; // ���ü���

    };
public:
	SSharedPtr();
	SSharedPtr(T* p);
	SSharedPtr(SSharedPtr<T>& other);// �������캯��,���ü���+1
	~SSharedPtr();

	// ��������=,����������ü���-1,���ж��Ƿ�delete;���Ҷ���+1;
	SSharedPtr<T> & operator = (SSharedPtr& other);
	// ����ָ�����*,->
	T& operator *();
	T* operator ->();

    size_t GetRefCount();	//ȡ�����ô���
	T* GetRefPtr();		//ȡ������ָ��
private:
    PtrInfo* m_pShread; // ���ü���
};

template <class T>
SSharedPtr<T>::PtrInfo::PtrInfo(T* p)
{
    m_pTtr = p;
    m_RefCount = 1;
}

template <class T>
SSharedPtr<T>::PtrInfo::~PtrInfo()
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
SSharedPtr<T>::SSharedPtr()
{
	m_pShread = NULL;
}

template<class T>
SSharedPtr<T>::SSharedPtr(T* p)
{
	//Ϊÿһ����ָ��newһ��
	m_pShread = new PtrInfo(p);
}

template <class T>
SSharedPtr<T>::SSharedPtr(SSharedPtr<T>& other)
{
	this->m_pShread = other.m_pShread;
	++(m_pShread->m_RefCount);
}

template <class T>
SSharedPtr<T>& SSharedPtr<T>::operator=(SSharedPtr& other)
{
	// ���Ҳ����������ü���+1
	++(other.m_pShread->m_RefCount);

	// �������������ָ�����¶���,��Ҫ��������-1;
	// ͬʱҲ��ֹ���Ը�ֵ�ķ�ʽ.
	// ����Ҫ�ж���������Ƿ��Ѿ�ָ������������,�������Ҫ!��ֹ��ָ�����Ϊnull�����.
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
T& SSharedPtr<T>::operator *()
{
	return *(m_pShread->m_pTtr);
}

template <class T>
T* SSharedPtr<T>::operator->()
{
	return (m_pShread->m_pTtr);
}

template <class T>
SSharedPtr<T>::~SSharedPtr()
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
size_t SSharedPtr<T>::GetRefCount()
{
	if (m_pShread)
		return m_pShread->m_RefCount;
	return 0;
}
template <class T>
T* SSharedPtr<T>::GetRefPtr()
{
	if (m_pShread)
		return (m_pShread->m_pTtr);
	return NULL;
}

#endif