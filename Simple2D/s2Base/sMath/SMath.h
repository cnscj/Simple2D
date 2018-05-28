#ifndef _SXMATH_H_
#define _SXMATH_H_
#include <cmath>
#include <ctime>
#include <cstdlib>
namespace SMath
{
    static const float Pi = 3.141592654f;   //圆周率
    static const float E = 2.718281828f;   //自然对数

    ////////////////////////////////////////////////
    ///				常用数学操作函数			 ///
    ////////////////////////////////////////////////
    //提取小数部分
    float GetFracPath(float  x);
    //比较浮点数
    bool EqualFloat(float a, float b, float fEpsilon = 1e-6f);
    //取得位数
    int GetBitCount(int num, int radis = 10);
    int GetBitCount(float num, int radis = 10);
    //随机数种子
    unsigned int RandRoot();
    //取得随机数
    int Random(int x, int y);
    //取得随机数,bit为精确位数
    float Random(float x, float y, int bit);
    //取得随机数,bit为精确位数
    float Random(float x, float y);
    
    //雷神之锤-卡马克-倒数开方
    float InvSqrt(float x);
    //概率数返回下标,arr为概率数组
    int RandomProb(double arr[], int size);
};


#endif