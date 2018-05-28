/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-07 12:48:14 
 * @Brief: æ± 
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-17 11:33:13
 * @Last Modified log: 
 */
#ifndef _SMEMORY_SPOOL_H_
#define _SMEMORY_SPOOL_H_
#include "SReference.h"
class SPool : public SReference
{
public:
    //清空池
    virtual void Clear() = 0;

    //清理池
    virtual void Purge() {Clear();}
};
#endif