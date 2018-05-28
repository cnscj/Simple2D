/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-03-07 00:00:00 
 * @Brief: 自定义类型
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-08 12:09:16
 * @Last Modified log: 
 */

#ifndef _S2TYPE_H_
#define _S2TYPE_H_


#if defined(_MSC_VER) && _MSC_VER < 1800
#error Visual Stuidio earlier than 2013 is no long supported.
#else
#include <cstdint>
#endif


#if defined __GNUC__ || defined __APPLE__
#include <ext/hash_map>
#include <ext/hash_set>

#define  __S2NS __gnu_cxx
#else
#include <hash_map>
#include <hash_set>
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#define  __S2NS std
#endif


////////////////////////////////////////////////////
#include <list>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <functional>
#include <string>
#include "../s2Base/sMath/SBasePoint2.hpp"
#include "../s2Base/sMath/SBaseSize.hpp"
#include "../s2Base/sMath/SBaseRect.hpp"
#include "../s2Base/sMath/SBaseVector2.hpp"
#include "../s2Base/sMath/SBaseVector3.hpp"
#include "../s2Base/sMath/SBaseMatrix.hpp"

typedef bool                S2Bool;   ///< @brief 逻辑型
typedef char                S2Char;   ///< @brief 字符型
typedef wchar_t             S2CharW;  ///< @brief 宽字符
typedef uint8_t             S2Byte;   ///< @brief 字节型
typedef int16_t             S2Short;  ///< @brief 16位短整数
typedef uint16_t            S2uShort; ///< @brief 16位无符号短整数
typedef int32_t             S2Int;    ///< @brief 32位整数
typedef uint32_t            S2uInt;   ///< @brief 32位无符号整数
typedef int64_t             S2Long;   ///< @brief 64位长整数
typedef uint64_t            S2uLong;  ///< @brief 64位无符号长整数
typedef float               S2Float;  ///< @brief 浮点型
typedef double              S2Double; ///< @brief 双精度浮点型
typedef S2Char*             S2Str;    ///< @brief C式字符串
typedef const S2Char*       S2cStr;   ///< @brief C式字符串常量
typedef S2CharW*            S2StrW;   ///< @brief C式宽字符串
typedef const S2CharW*      S2cStrW;  ///< @brief C式宽字符串常量

typedef std::string         S2String; ///< @brief 字符串
typedef std::wstring        S2WString;///< @brief 宽字符串

typedef S2uLong             S2dWord;  ///< @brief 双字型
typedef S2uShort            S2Word;   ///< @brief 字型

typedef S2dWord             S2ColorRef;///< @brief 双字型表示的颜色
typedef S2Byte*             S2Data;   ///< @brief 内存数据指针
typedef const S2Byte*       S2cData;  ///< @brief 常量内存数据指针
typedef S2uLong             S2Len;    ///< @brief 长度型
typedef S2Int               S2Result; ///< @brief 预定义返回值

typedef SBasePoint2<int>    S2Point;  ///< @brief 点
typedef SBaseRect<int>      S2Rect;   ///< @brief 矩形
typedef SBaseSize<int>      S2Size;   ///< @brief 尺寸
typedef SBaseVector2<>      S2Vector2;///< @brief 2维向量
typedef SBaseVector3<>      S2Vector3;///< @brief 2维向量
typedef SBaseMatrix<>       S2Matrix; ///< @brief 4*4矩阵



////////////////////////////////////////////////////
template<class K, class V, class C = std::less<K> >
using S2Map = std::map<K, V, C>;

template<class K, class V, class C = std::less<K> >
using S2HashMap = __S2NS::hash_map<K, V, C>;

template<class T>
using S2Array = std::vector<T>;

template<class T>
using S2List = std::list<T>;

template<class T>
using S2Stack = std::stack<T>;

template<class T>
using S2Queue = std::queue<T>;

template<class T>
using S2Function = std::function<T>;

template<class K, class C = std::less<K> >
using S2Set = std::set<K, C>;
template<class K, class C = std::less<K> >
using S2MultiSet = std::multiset<K, C>;

template<class K, class C = std::less<K> >
using S2HashSet = __S2NS::hash_set<K, C>;

template<class K, class V>
using S2Pair = std::pair<K, V>;



#endif //_S2TYPE_H_
