/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-26 08:53:45 
 * @Brief: 资源管理器
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-26 13:09:04
 * @Last Modified log: 
 */
#ifndef _S2RESOURCEMANAGER_H_
#define _S2RESOURCEMANAGER_H_
#include "../s2Base/sParse/SMD5.h"
#include "../s2Base/sLang/SValue.h"
#include "../s2Core/S2Singleton.hpp"
class S2ResourceManager : public S2Singleton<S2ResourceManager>
{
public:
    S2ResourceManager();
    ~S2ResourceManager();

};
#endif