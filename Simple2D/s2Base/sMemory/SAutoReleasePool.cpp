#include "SAutoReleasePool.h"

SAutoReleasePool::SAutoReleasePool()
{
    m_pObjectArray = new std::list<SReference *>();
}
SAutoReleasePool::~SAutoReleasePool()
{
    Clear();

    delete m_pObjectArray;
    m_pObjectArray = NULL;
}

// 将对象添加到自动释放池  
void SAutoReleasePool::AddObject(SReference *pRef)
{
    //Push进队列中
    m_pObjectArray->push_back(pRef);

    //这里不进行引用持有,这里并不是长期持有
}

// 将对象从自动释放池中移除  
void SAutoReleasePool::RemoveObject(SReference *pRef)
{
    //从自动释放池中移除对象，使该对象不被自动释放池管理，当然也不会自动释放
    //因为AddObject被没有使引用计数增加，所有这里也不能使应用计数有变化 
    //遍历移除
    for (auto &it = m_pObjectArray->begin(); it != m_pObjectArray->end(); )
    {
        if (*it == pRef)
        {
            //从池中移除
            m_pObjectArray->erase(it++);
        }
        else ++it;
    }
    
}

// 将自动释放池中的对象释放掉  
void SAutoReleasePool::Clear()
{
    //遍历释放对象
    for (auto &it = m_pObjectArray->begin(); it != m_pObjectArray->end();)
    {
        //XXX:未经测试

        if ((*it)->m_unRefCount >= (*it)->m_unManagedCount)
        {
            --(*it)->m_unManagedCount;
            (*it)->Release();
            m_pObjectArray->erase(it++);
        }
        else{
            --(*it)->m_unManagedCount;
            m_pObjectArray->erase(it++);
        }
            

    }
}

void SAutoReleasePool::Purge()
{
    Clear();
}