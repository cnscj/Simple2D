#include "S2DebugUtil.h"
#include <stdarg.h>
#include <string>
#include <iostream>
#include <windows.h>
void S2DebugUtil::Print(const TCHAR* pszFormat, ...)
{
	TCHAR str[256];
	va_list args;
	va_start(args, pszFormat);
	_vstprintf_s(str, pszFormat, args);
	OutputDebugString(str);
	va_end(args);

}

void S2DebugUtil::PrintLn(const TCHAR* pszFormat, ...)
{
	TCHAR str[256];
	va_list args;
	va_start(args, pszFormat);
    _vstprintf_s(str, pszFormat, args);
	OutputDebugString(str);
	OutputDebugString(TEXT("\n"));
	va_end(args);
}
