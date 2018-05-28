#include "SMath.h"

static unsigned int g_ramdon_root_count = SMath::RandRoot();
////
unsigned int SMath::RandRoot()
{
    ::srand((unsigned)::time(nullptr));
    return g_ramdon_root_count + 1;
}

//提取小数部分
float SMath::GetFracPath(float  x)
{
    return (float)((float)x - (int)x);
}

//比较浮点数
bool SMath::EqualFloat(float a, float b, float fEpsilon)
{
    return (::fabs(a - b) < fEpsilon);
}

//取得位数
int SMath::GetBitCount(int num, int radis)
{
    int bit = 0;
    do
    {
        num /= radis;
        bit++;
    } while (num != 0);
    return bit;
}
int SMath::GetBitCount(float num, int radis)
{
    int integer = int(num);
    int bit = GetBitCount(integer, radis);
    float flo = GetFracPath(num);

    if (integer == 0 && !EqualFloat(flo, 0.f))bit = 0;
    else if (integer != 0 && flo == 0)return bit;

    //FIXME:存在精度误差,可能不准
    do
    {
        flo *= radis;
        bit++;
    } while (!EqualFloat(flo - (int)flo, 0.f));
    return bit;
}

//取得随机数
int SMath::Random(int x, int y)
{
    //::srand((unsigned)::time(nullptr));//随机数种子，以时间为变化单位
    int ret = ::rand() % (y - x + 1) + x; //随机数范围X~Y
    return ret;
}
//取得随机数,bit为精确位数
float SMath::Random(float x, float y, int bit)
{
    //::srand((unsigned)::time(nullptr));//随机数种子，以时间为变化单位
    int pre = (int)pow(10.0f, bit);
    int newx = (int)x*pre;
    int newy = (int)y*pre;
    int ret = ::rand() % (newy - newx + 1) + newx; //随机数范围X~Y
    float newret = (float)ret / pre;
    return newret;
}
//取得随机数,bit为精确位数
float SMath::Random(float x, float y)
{
    int bit = 0;
    int xbit = GetBitCount(GetFracPath(x));
    int ybit = GetBitCount(GetFracPath(y));
    bit = xbit > ybit ? xbit : ybit;
    return Random(x, y, bit);
}

//雷神之锤-卡马克-倒数开方
float SMath::InvSqrt(float x)
{
    float xhalf = 0.5f * x;
    int i = *(int *)&x;
    i = 0x5f3759df - (i >> 1);
    x = *(float *)&i;
    x = x * (1.5f - xhalf * x * x);
    return x;
}

int SMath::RandomProb(double arr[], int size)
{
    double total = 0;
    for (int i = 0; i < size; ++i)
        total += arr[i];
    if (size == 0 || total <= 0)
        return -1;

    int num = Random(0, 100);
    double left, right = 0;
    for (int j = 0; j < size; ++j)
    {
        left = right;
        right = right + ((arr[j] * 100) / total);
        if (left < num && num <= right)
            return j;
    }
    return -1;
}
