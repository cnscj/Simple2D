/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-17 10:06:02 
 * @Brief: 
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-17 11:34:21
 * @Last Modified log: 
 */
#include "SValue.h"
#include <stdarg.h>
#include <stdlib.h>
#include <algorithm>
SValue::SValue()
:m_strValue("")
{
    
}
SValue::SValue(void *v)
{
   m_strValue = parse("%ld",v);
}
SValue::SValue(bool v)
{
   m_strValue = parse("%s",v);
}
SValue::SValue(short v)
{
    m_strValue = parse("%d",v);
}
SValue::SValue(char v)
{
    m_strValue = parse("%c",v);
}
SValue::SValue(const char *frm, ...)
{
    //FIXME:不能识别当...为std::string的情况,会产生误差
    char buffer[512];
    
    va_list ap;
    va_start(ap, frm);

    #if defined __GNUC__ || defined __APPLE__
        vsprintf(buffer, frm, ap);
    #else
        vsprintf_s(buffer, frm, ap);
    #endif

    va_end(ap);
    
    m_strValue = std::string(buffer);
}
SValue::SValue(std::string frm,...)
{
    char buffer[512];
    const char *fmtsz = (const char *)frm.c_str();
    va_list ap;
    va_start(ap,fmtsz) ;
    #if defined __GNUC__ || defined __APPLE__
        vsprintf(buffer, fmtsz, ap);
    #else
        vsprintf_s(buffer, fmtsz, ap);
    #endif

    va_end(ap);
    
    m_strValue = std::string(buffer);
}
SValue::SValue(int v)
{
   m_strValue = parse("%d",v);
}
SValue::SValue(unsigned int v)
{
    m_strValue = parse("%d",v);
}
SValue::SValue(float v)
{
   m_strValue =  parse("%f",v);
}
SValue::SValue(double v)
{
    m_strValue = parse("%f",v);
}
SValue::SValue(long v)
{
   m_strValue = parse("%ld",v);
}
SValue::SValue(long long v)
{
   m_strValue = parse("%ll",v);
}
SValue::SValue(unsigned long v)
{
       m_strValue = parse("%lu",v);
}
/////
void SValue::SetStrValue(std::string value)
{
    m_strValue = value;
}
const std::string &SValue::GetStrValue() const
{
    return m_strValue;
}

std::string SValue::ToString()
{
    return m_strValue;
}
bool SValue::ToBool()
{
    std::string ret = m_strValue;
    std::transform(ret.begin(), ret.end(), ret.begin(), ::toupper);
    if (ret == "TRUE")return true;
    else return false;
}

int SValue::ToInt()
{
    unsigned int result = atoi(m_strValue.c_str());
    return result;
}
int SValue::ToUnsignedInt()
{
    int result = (int)strtod(m_strValue.c_str(), nullptr);
    return result;
}
char SValue::ToChar()
{
    if(m_strValue.size() >0 )
        return m_strValue.at(0);
    return 0;
}
float SValue::ToFloat()
{
    float result = (float)atof(m_strValue.c_str());
    return result;
}
double SValue::ToDouble()
{
    double result = strtod(m_strValue.c_str(), nullptr);
    return result;
}
long SValue::ToLong()
{
    long result = strtol(m_strValue.c_str(), nullptr,10);
    return result;
}
long long SValue::ToLongLong()
{
    long long result = strtoll(m_strValue.c_str(), nullptr,10);
    return result;
}
unsigned long SValue::ToUnsignedLong()
{
    unsigned long result = strtoul(m_strValue.c_str(), nullptr,10);
    return result;
}
std::string SValue::ToHex(const char *fmt)
{
    std::string ret,rsfmt(fmt);
    int len = sizeof(char)*( 8 / 4 + 2 + 1);
    char *hex = new char[len];
    for (int i = 0; i != m_strValue.size(); ++i)
    {
    #if defined __GNUC__ || defined __APPLE__
            sprintf(hex, "%x", (char)m_strValue.at(i));
    #else
        sprintf_s(hex, len, "%x", (char)m_strValue.at(i));
    #endif

        ret += hex + rsfmt;
    }
    delete[] hex;
    return ret;
}
std::string SValue::ToBin(const char *fmt)
{
    std::string ret,rsfmt(fmt);
    int len = sizeof(char)*(32);
    char *metaBinChar = new char[len];
    for (int i = 0; i != m_strValue.size(); ++i)
    {
        itoa_bin((char)m_strValue.at(i),metaBinChar);
        ret += metaBinChar + rsfmt;
    }
    delete[] metaBinChar;
    return ret;
}

//
std::string SValue::parse(const char *frm, ...)
{
    char buffer[512];   // 分配512字节的字符串缓存
    
    va_list ap;
    va_start(ap, frm);
    #if defined __GNUC__ || defined __APPLE__
        vsprintf(buffer, frm, ap);    // 将格式字符串与后面的参数绑定为一个字符串，拷贝到输出缓存
    #else
        vsprintf_s(buffer, frm, ap);    // 将格式字符串与后面的参数绑定为一个字符串，拷贝到输出缓存
    #endif
   
    va_end(ap);
    
    return std::string(buffer);
}

int SValue::itoa_bin(unsigned int data, char *str)
{
    if(str == NULL)
        return -1;
    
    char *start = str;
    
    while(data)
    {
        if(data & 0x1)
            *str++ = 0x31;
        else
            *str++ = 0x30;
        
        data >>= 1;
    }
    
    *str = 0;
    
    //reverse the order
    char *low, *high, temp;
    low = start;high = str - 1;
    
    while(low < high)
    {
        temp = *low;
        *low = *high;
        *high = temp;
        
        ++low;
        --high;
    }
    
    return 0;
}

////
