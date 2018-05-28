/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-27 09:31:41 
 * @Brief: 字符串类
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-19 12:18:34
 * @Last Modified log: 
 */
#ifndef _SSTRING_H_
#define _SSTRING_H_
#include <string>
class SString
{
public:
    friend std::ostream& operator <<(std::ostream&, SString&);
    friend std::istream& operator >>(std::istream&, SString&);
public:
    SString();
    SString(const std::string &str);
    SString(const std::string &str, size_t pos, size_t n = std::string::npos);
    SString(const char *s, size_t n);
    SString(const char *s);
    SString(size_t n, char c);

    template<class InputIterator>
    SString(InputIterator begin, InputIterator end);

    //新增构造函数
    SString(char ch);
    SString(int x);
    SString(float x);
    SString(double x);
    SString(long x);
    SString(bool x);
    SString(const SString &str);
    virtual ~SString();
public:
    /* 原有函数 */
public:
    /* 新增函数 */
private:
    /* 宽窄字转换函数 */

    /* 取字串 */
    
private:
    //窄字符全部转化为宽字符
    std::wstring m_string;
};
#endif