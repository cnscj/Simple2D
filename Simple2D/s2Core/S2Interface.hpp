/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-19 15:37:27 
 * @Brief: 接口模板
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-19 15:49:06
 * @Last Modified log: 
 */
#ifndef _S2INTERFACE_H_
#define _S2INTERFACE_H_
#include "../s2Base/sPattern/SSingletonTemp.hpp"
#include "S2Object.h"
template<class T>
class S2Interface:
    public SSingletonTemp<T>,
    public S2Object
{
public:
    S2Interface(T *pInstance = nullptr) :SSingletonTemp(pInstance){}
    virtual ~S2Interface(){}
};

#endif