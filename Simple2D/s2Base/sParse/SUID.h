/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-26 13:23:30 
 * @Brief: 唯一标识
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-26 13:25:16
 * @Last Modified log: 
 */
#ifndef _SUID_H_
#define _SUID_H_

#include <string>
namespace SUID
{
    std::string CreateUUID();

    std::string CreateGUID();
   
};

#endif