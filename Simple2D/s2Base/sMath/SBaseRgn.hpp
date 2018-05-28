#ifndef _SXBASERGN_H_
#define _SXBASERGN_H_
template<class T = float>
class SBaseRgn
{
public:
    SBaseRgn(T x=0, T y=0, T width=0, T height=0);
public:
    T x, y, width, height;
};
template<class T>
SBaseRgn<T>::SBaseRgn(T x, T y, T width, T height)
:x(x), y(y), width(width), height(height)
{

}
#endif