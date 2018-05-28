/**
* @Author: cnscj
* @Version: v1.0
* @Date: 2018-04-27 09:31:33
* @Brief: 权值链表
* @Last Modified by: cnscj
* @Last Modified time: 2018-05-17 11:23:56
* @Last Modified log:
*/
#ifndef _SPRIORITYLIST_HPP_
#define _SPRIORITYLIST_HPP_
#include <list>
#include <algorithm>

template<class T, class C = std::less<T>>
class SPriorityList
{
public:
    typedef typename std::list<T>::const_iterator const_iterator;
    typedef typename std::list<T>::iterator iterator;
    typedef typename std::list<T>::const_reverse_iterator const_reverse_iterator;
public:
    SPriorityList();
    ~SPriorityList();
public:
    void Push(T value);
    void Remove(T value);
    T At(size_t index);
    void Clear();
    bool Empty();
    size_t Size();
    size_t Length();
    void Erase(const_iterator value);
    iterator Begin();
    iterator End();
    const_reverse_iterator RBegin();
    const_reverse_iterator REnd();
private:
    std::list<T>         m_list;
    C                    m_cmp;
};
template<class T, class C>
SPriorityList<T, C>::SPriorityList()
{

}
template<class T, class C>
SPriorityList<T, C>::~SPriorityList()
{

}

template<class T, class C>
void SPriorityList<T, C>::Push(T value)
{
    //选择合适的位置插入
    auto pList = &m_list;
    for (auto it = pList->begin(); it != pList->end(); ++it)
    {
        if (m_cmp(value, *it))
        {
            pList->insert(it, value);
            return;
        }
    }
    pList->push_back(value);


}

template<class T, class C>
void SPriorityList<T, C>::Remove(T value)
{
    return m_list.remove(value);
}

template<class T, class C>
T SPriorityList<T, C>::At(size_t index)
{
    return m_list.at(index);
}

template<class T, class C>
void SPriorityList<T, C>::Clear()
{
    return m_list.clear();
}

template<class T, class C>
bool SPriorityList<T, C>::Empty()
{
    return m_list.empty();
}

template<class T, class C>
size_t SPriorityList<T, C>::Size()
{
    return m_list.size();
}

template<class T, class C>
size_t SPriorityList<T, C>::Length()
{
    return m_list.size();
}

template<class T, class C>
void SPriorityList<T, C>::Erase(const_iterator it)
{
    return m_list.erase(it);
}

template<class T, class C>
typename SPriorityList<T, C>::iterator SPriorityList<T, C>::Begin()
{
    return m_list.begin();
}
template<class T, class C>
typename SPriorityList<T, C>::iterator SPriorityList<T, C>::End()
{
    return m_list.end();
}
template<class T, class C>
typename SPriorityList<T, C>::const_reverse_iterator SPriorityList<T, C>::RBegin()
{
    return m_list.rbegin();
}

template<class T, class C>
typename SPriorityList<T, C>::const_reverse_iterator SPriorityList<T, C>::REnd()
{
    return m_list.rend();
}

#endif