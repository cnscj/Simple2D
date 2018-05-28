/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-15 20:21:24 
 * @Brief: 值转换
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-19 12:44:58
 * @Last Modified log: 
 */
#ifndef _SVALUE_H_
#define _SVALUE_H_
#include <string>

class SValue
{
public:
    SValue();
    SValue(void *);
    SValue(bool v);
    SValue(short v);
    SValue(char v);
    SValue(const char *frm, ...);
    SValue(std::string frm, ...);
    SValue(int v);
    SValue(unsigned int v);
    SValue(float v);
    SValue(double v);
    SValue(long v);
    SValue(long long v);
    SValue(unsigned long v);
public:
    void SetStrValue(std::string value);
    const std::string &GetStrValue()const;
public:
    std::string ToString();
    bool ToBool();
    int ToInt();
    int ToUnsignedInt();
    char ToChar();
    float ToFloat();
    double ToDouble();
    long ToLong();
    long long ToLongLong();
    unsigned long ToUnsignedLong();
    std::string ToHex(const char *fmt = "");
    std::string ToBin(const char *fmt = "");

private:
    std::string parse(const char *frm, ...);
    int itoa_bin(unsigned int data, char *str);
private:
    std::string m_strValue;
};
#endif
