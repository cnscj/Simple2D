/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-03-07 00:00:00 
 * @Brief: 相关宏定义
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-07 16:55:40
 * @Last Modified log: 
 */

#ifndef _S2MACRO_H_
#define _S2MACRO_H_
#include"S2Type.h"

//释放指针                   
#define S2SAFEDELETE(p)        { if(p) { delete (p); (p)=nullptr; } }//安全
#define S2DELETE(p)            { if(p) { delete (p); } }//非安全
//释放指针数组
#define S2SAFEDELETEARRAY(p)   { if(p) { delete[] (p); (p)=nullptr; } }//安全
#define S2DELETEARRAY(p)       { if(p) { delete[] (p); } }//非安全
//释放接口
#define S2SAFERELEASE(p)       { if(p) {p->Release();(p)=nullptr; } }//安全
#define S2RELEASE(p)           { if(p) {p->Release();} }//非安全

//
#define S2RESULT_PTR(p)        { p?p:nullptr; }
#define S2RESULT_IS(p)         { p?true:false; }

//颜色生成宏
#ifndef S2COLOR_ARGB
#define S2COLOR_ARGB(a,r,g,b) ((S2ColorRef)((((a)& 0xff) << 24) | (((r)& 0xff) << 16) | (((g)& 0xff) << 8) | ((b)& 0xff)))
#define S2COLOR_XRGB(r,g,b)  S2COLOR_ARGB(0xff,r,g,b)
#define S2COLOR_RGB(r,g,b)   S2COLOR_XRGB(r,g,b)

#define S2COLOR_BLACK S2COLOR_RGB(0,0,0)                //定义黑色
#define S2COLOR_WHITE S2COLOR_RGB(255,255,255)          //定义白色
#endif

//字符串


//文字格式宏


//错误返回
//错误码定义
////////////////////////////////////////////////////////////////////////////////
/// @brief     判断S2Result是否成功
/// @param[in] sr 要判断的返回值
#define S2OK(sr)     (((S2Result)(sr)) >= 0)

/// @brief     判断S2Result是否失败
/// @param[in] fr 要判断的返回值
#define S2FAILED(sr) (((S2Result)(sr)) <  0)

/// @brief 生成一个S2Result错误
/// @param[in] code 错误实体部分
#define S2MAKEERR(code)           ((S2Result) (0x80000000 | ((S2uInt)(code))))

/// @brief          生成一个S2Result返回值
/// @param[in] sev  严重程度，0=成功，1=失败
/// @param[in] code 错误实体部分
#define S2MAKERET(sev,code)       ((S2Result) (((S2uInt)(sev)<<31) | ((S2uInt)(code))))

/// @brief          生成一个S2Result返回值
/// @param[in] sev  严重程度，0=成功，1=失败
/// @param[in] rsv  保留值，默认取0
/// @param[in] desc 错误描述
#define S2MAKERETEX(sev,rsv,desc) ((S2Result) (((S2uInt)(sev)<<31) | ((S2uInt)(rsv)<<16) | ((S2uInt)(desc))))

/// @brief     返回错误描述
/// @param[in] sr 要处理的返回值
#define S2RESULT_CODE(fr)     ((sr) & 0xFFFF)

/// @brief     返回错误保留值
/// @param[in] sr 要处理的返回值
#define S2RESULT_RSV(sr)      (((sr) >> 16) & 0x7FFF)

/// @brief     返回错误严重程度
/// @param[in] fr 要处理的返回值
/// @return    0=成功， 1=失败
#define S2RESULT_SXVERITY(sr) (((sr) >> 31) & 0x1)

////////////////////////////////////////////////////////////////////////////////
// 常见错误
////////////////////////////////////////////////////////////////////////////////
/// @addtogroup fancy常见返回值
/// @brief fancy库中的常见错误
/// @note  仅当FCYRESULT_RSV返回值为0时用来表示常见错误
/// @{

#define S2ERR_OK               ((S2Result)0) ///< @brief 正常返回值
#define S2ERR_UNKNOWN          S2MAKEERR(0)  ///< @brief 未知返回值
#define S2ERR_INTERNALERR      S2MAKEERR(1)  ///< @brief 内部错误
///< @details 通常表示API调用失败
#define S2ERR_ILLEGAL          S2MAKEERR(2)  ///< @brief 无效调用
#define S2ERR_NOTIMPL          S2MAKEERR(3)  ///< @brief 未实现
#define S2ERR_NOTSUPPORT       S2MAKEERR(4)  ///< @brief 不支持
#define S2ERR_INVAILDDATA      S2MAKEERR(5)  ///< @brief 无效数据
#define S2ERR_INVAILDPARAM     S2MAKEERR(6)  ///< @brief 无效参数
#define S2ERR_INVAILDVERSION   S2MAKEERR(7)  ///< @brief 无效版本
#define S2ERR_OBJNOTEXSIT      S2MAKEERR(8)  ///< @brief 对象不存在
#define S2ERR_OBJEXSITED       S2MAKEERR(9)  ///< @brief 对象已存在
#define S2ERR_OUTOFRANGE       S2MAKEERR(10) ///< @brief 超出范围
///< @details 文件、数组访问到达结尾或越界
#define S2ERR_OUTOFMEM         S2MAKEERR(11) ///< @brief 内存不足


#endif