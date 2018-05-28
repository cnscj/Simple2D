#include "SAutoReleasePoolManager.h"
SAutoReleasePoolManager *SAutoReleasePoolManager::g_pPoolManager = NULL;

//取得实例
SAutoReleasePoolManager *SAutoReleasePoolManager::GetInstance()
{
    if (!g_pPoolManager)
        g_pPoolManager = new SAutoReleasePoolManager();
    return g_pPoolManager;
}

//销毁实例
void SAutoReleasePoolManager::DestroyInstance()
{
    delete g_pPoolManager;
    g_pPoolManager = NULL;
}
////////
SAutoReleasePoolManager::SAutoReleasePoolManager()
{
    m_pAutoReleasePoolStack = new std::list<SAutoReleasePool *>();

    //指向自动释放池队列的末尾节点
    m_pCurReleasePool = NULL;
}
SAutoReleasePoolManager::~SAutoReleasePoolManager()
{
    //清空所有池
    Finalize();

    m_pCurReleasePool = NULL;

    //删除自动释放栈
    delete m_pAutoReleasePoolStack;
    m_pAutoReleasePoolStack = NULL;

}

//添加对象
void SAutoReleasePoolManager::AddObject(SReference *pRef)
{
    GetCurReleasePool()->AddObject(pRef);
}

//移除对象
void SAutoReleasePoolManager::RemoveObject(SReference *pRef)
{
    m_pCurReleasePool->RemoveObject(pRef);
}

// 清空所有的自动释放池  
void SAutoReleasePoolManager::Finalize()
{
    for (auto &it = m_pAutoReleasePoolStack->begin(); it != m_pAutoReleasePoolStack->end();)
    {
        //移除释放所有池
        delete *it;
        m_pAutoReleasePoolStack->erase(it++);
    }

}

// 增加一个自动释放池  
void SAutoReleasePoolManager::Push()
{
    SAutoReleasePool *pPool = new SAutoReleasePool();
    m_pCurReleasePool = pPool;

    m_pAutoReleasePoolStack->push_back(pPool);

}

// 移除一个自动释放池，即移除当前自动释放池  
void SAutoReleasePoolManager::Pop()
{
    // 清理自动释放池队列，只剩下队列中的第一个自动释放池  
    // 剩下的这个自动释放池中的对象也要清理掉  
    // 这个函数便是自动释放池管理者，实现自动释放池内对象的实现了  
    if (!m_pCurReleasePool)
    {
        return;
    }

    // 清理当前的自动释放池  
    m_pCurReleasePool->Clear();

    // 保持池中只有一个对象池
    int nCount = m_pAutoReleasePoolStack->size();
    if (nCount > 1)
    {
        // 如果自动释放池队列中有超过一个自动释放池  
        // 将末端的自动释放池清理并移除
        delete m_pAutoReleasePoolStack->back();
        m_pAutoReleasePoolStack->pop_back();
        m_pCurReleasePool = (SAutoReleasePool*)m_pAutoReleasePoolStack->back();
    }
}
//清理池
void SAutoReleasePoolManager::Purge()
{
    //每一帧调用,对释放池对象进行一次Release()操作
    Pop();
}


//
//取得当前自动释放池
SAutoReleasePool *SAutoReleasePoolManager::GetCurReleasePool()
{
    // 获取当前的自动释放池  
    // 如果当前的自动释放池为空，说明自动释放池队列中也为空  
    // 通过push方法，添加新的自动释放池  
    if (!m_pCurReleasePool)
    {
        Push();
    }

    return m_pCurReleasePool;
}