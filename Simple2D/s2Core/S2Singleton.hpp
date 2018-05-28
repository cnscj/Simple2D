/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-19 15:36:53 
 * @Brief: 单例模式
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-19 15:48:19
 * @Last Modified log: 
 */
#ifndef _S2SINGLETON_H_
#define _S2SINGLETON_H_
#include "../s2Base/sPattern/SSingleton.hpp"
#include "S2Object.h"
template<class T>
class S2Singleton:
    public SSingleton<T>,
    public S2Object
{
public:
    S2Singleton(T *pInstance = nullptr) :SSingleton(pInstance){}
    virtual ~S2Singleton(){}
};

#endif