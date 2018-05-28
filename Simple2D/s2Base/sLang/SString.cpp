#include "SString.h"

SString::SString()
:m_string()
{

}
SString::SString(const std::string &str)
:m_string(str)
{

}
SString::SString(const std::string &str, size_t pos, size_t n = std::string::npos):
m_string(str, pos, n)
{

}
SString::SString(const char *s, size_t n)
:m_string(s, n)
{

}
SString::SString(const char *s)
:m_string(s)
{

}
SString::SString(size_t n, char c)
:m_string(n, c)
{

}

template<class InputIterator>
SString::SString(InputIterator begin, InputIterator end)
:m_string(begin, end)
{

}

//新增构造函数
SString::SString(char ch)
{

}
SString::SString(int x)
{

}
SString::SString(float x)
{

}
SString::SString(double x)
{

}
SString::SString(long x)
{

}

SString::SString(bool x)
{

}
SString::SString(const SString &str)
{

}
SString::~SString()
{

}