/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-27 14:47:04 
 * @Brief: 调试工具
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-27 15:13:29
 * @Last Modified log: 
 */
#ifndef _S2DEBUGUTIL_H_
#define _S2DEBUGUTIL_H_
#include <tchar.h>
namespace S2DebugUtil
{
    void Print(const TCHAR* pszFormat,...);
    void PrintLn(const TCHAR* pszFormat,...);
};

#endif
