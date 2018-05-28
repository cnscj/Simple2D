/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-19 13:54:26 
 * @Brief: 包装类
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-19 13:54:59
 * @Last Modified log: 
 */
#ifndef _S2WRAPPER_H_
#define _S2WRAPPER_H_
#include "../s2Base/sLang/SWrapper.h"
#include "S2Object.h"
class S2Wrapper : 
    public SWrapper,
    public S2Object
{
public:
    S2Wrapper();
    ~S2Wrapper();
public:

};

#endif