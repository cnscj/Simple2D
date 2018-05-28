/**
* SBaseSize½á¹¹Ìå
* ³ß´ç
* @author ZeroX
* @version v1.0 03/09/2017
*/
#ifndef _SXBASESIZE_H_
#define _SXBASESIZE_H_
template<class T = int>
class SBaseSize
{
public:
    SBaseSize(const SBaseSize &size);
    SBaseSize(T width = 0, T height = 0);

    T GetWidth() const;
    T GetHeight() const;

    bool operator ==(const SBaseSize &size)const;
    SBaseSize &operator =(const SBaseSize &size);
public:
    
    T width, height;
    //T &cx = width, &cy = height;
};

template<class T>
SBaseSize<T>::SBaseSize(const SBaseSize &size)
{
    this->width = size.width;
    this->height = size.height;
}
template<class T>
SBaseSize<T>::SBaseSize(T width, T height)
:width(width), height(height)
{

}

template<class T>
T SBaseSize<T>::GetWidth() const
{
    return width;
}

template<class T>
T SBaseSize<T>::GetHeight() const
{
    return height;
}

template<class T>
bool SBaseSize<T>::operator ==(const SBaseSize &size)const
{
    if (this->width == size.width && this->height == size.height)
        return true;
    else return false;
}
template<class T>
SBaseSize<T> &SBaseSize<T>::operator =(const SBaseSize &size)
{
    this->width = size.width;
    this->height = size.height;
    return *this;
}
#endif