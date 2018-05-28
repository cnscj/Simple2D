/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-27 15:20:58 
 * @Brief: 异常类
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-27 15:38:07
 * @Last Modified log: 
 */

#ifndef _SEXCEPTION_H_
#define _SEXCEPTION_H_
#include "SThrowable.h"
class SException : public SThrowable
{
private:
	int m_nTime;			//异常时间
	char m_szOri[128];		//异常来源
	char m_szDesc[256];		//记录异常问题描述

public:
	SException();
	~SException();
public:
	virtual int GetTime();
	virtual void Print();
	virtual void PrintException();

};

#endif