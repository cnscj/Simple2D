/**
 * @Author: freeangeles 
 * @Version: v1.0 
 * @Date: 2015-10-16 10:38:0 
 * @Brief: 对象池
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-17 11:27:45
 * @Last Modified log: 
 */
#ifndef _SOBJETPOOL_H_
#define _SOBJETPOOL_H_
#include <vector>
#include <queue>
#include <cstdlib>
#include <cassert>
#include "SPool.h"
template<class T>
class SObjectPool :public SPool
{
public:
    //初始化块大小如果能预先估算出块大小则性能达到最大
    //即:只分配一次内存只释放一次内存
    SObjectPool(size_t ChunkSize = 32);
    virtual ~SObjectPool();
public:
    //设置块大小
    void SetChunkSize(size_t ChunkSize);

    //模拟new关键字分配内存并调用构造函数
    T* New();

    //模拟delete关键字释放内存调用析构函数
    void Delete(T *pT);

    //清空池
    void Clear();
private:
    //分配块大小
    void AllocateChunk(size_t ChunkSize);

    //释放块
    void ReleaseChunk();
private:
    //空闲池
    std::queue< T* > m_queFreePool;
    //块池
    std::vector< T* > m_vecChunkPool;

    //当前块大小
    size_t m_stChunkSize;
};

template< typename T >
SObjectPool< T >::SObjectPool(size_t ChunkSize)
:m_stChunkSize(ChunkSize)
{}

template< typename T >
SObjectPool< T >::~SObjectPool()
{
    ReleaseChunk();
}

template< typename T >
void SObjectPool< T >::SetChunkSize(size_t ChunkSize)
{
    if (0 == ChunkSize)
    {
        assert(false);
        return;
    }
    m_stChunkSize = ChunkSize;
    if (m_queFreePool.empty())
    {
        return;
    }
    if (m_queFreePool.size() < m_stChunkSize)
    {
        AllocateChunk(m_stChunkSize - m_queFreePool.size());
    }
}

template< typename T >
T* SObjectPool< T >::New()
{
    if (m_queFreePool.empty())
    {
        AllocateChunk(m_stChunkSize);
    }
    if (m_queFreePool.empty())
    {
        assert(false);
        return nullptr;
    }
    T* pT = m_queFreePool.front();
    m_queFreePool.pop();
    new(pT)T();
    return pT;
}

template< typename T >
void SObjectPool< T >::Delete(T *pT)
{
    if (nullptr == pT)
    {
        assert(false);
        return;
    }
    pT->~T();
    m_queFreePool.push(pT);
}

template< typename T >
void SObjectPool< T >::Clear()
{
    ReleaseChunk();
}

template< typename T >
void SObjectPool< T >::AllocateChunk(size_t ChunkSize)
{
    if (0 == ChunkSize)
    {
        assert(false);
        return;
    }
    T* pT = reinterpret_cast< T* >(::malloc(ChunkSize * sizeof(T)));
    if (nullptr == pT)
    {
        assert(false);
        return;
    }

    for (size_t i = 0; i < ChunkSize; ++i)
    {
        m_queFreePool.push(pT + i);
    }
    m_vecChunkPool.push_back(pT);
}

template< typename T >
void SObjectPool< T >::ReleaseChunk()
{
    for (size_t i = 0; i < m_vecChunkPool.size(); ++i)
    {
        free(m_vecChunkPool[i]);
        m_vecChunkPool[i] = nullptr;
    }
    m_vecChunkPool.clear();
}
#endif