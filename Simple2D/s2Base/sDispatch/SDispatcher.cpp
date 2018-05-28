#include <thread>
#include "SDispatcher.h"

SDispatcher::SDispatcher()
{
    m_pListenerMap = new std::unordered_map<SEvent::Type,std::list<SEventListener *>*>();
    m_pEventQueue = new std::priority_queue<SEvent *,std::vector<SEvent *>,EventCmp>();
    m_pqueDirtyEvents = new std::queue<std::pair<unsigned int ,SEvent *> >();
    m_pqueDirtyListeners = new std::queue<std::pair<unsigned int ,SEventListener *> >();
}
SDispatcher::~SDispatcher()
{

    delete m_pListenerMap;
    delete m_pEventQueue;
    delete m_pqueDirtyEvents;
    delete m_pqueDirtyListeners;
}


//添加监听器
bool SDispatcher::AddEventListener(SEventListener *pListener,unsigned int flag)
{
    return AddEventListener(pListener,pListener->GetSource(),flag);
}

bool SDispatcher::AddEventListener(SEventListener *pListener, const void *pSource, unsigned int flag)
{
    return AddEventListenerWithFixedPriority(pListener, pSource, SDispatcher::MINPRIORITY);
}
//以优先级添加监听器
bool SDispatcher::AddEventListenerWithFixedPriority(SEventListener *pListener,unsigned int flag)
{
    return AddEventListenerWithFixedPriority(pListener,pListener->GetSource(),pListener->GetPriority(),flag);
}
bool SDispatcher::AddEventListenerWithFixedPriority(SEventListener *pListener, const void *pSource, int priority, unsigned int flag)
{
    if(pListener && !pListener->m_pDispatcher)
    {
        _InsertList(priority,pListener);
        pListener->m_pSource = (void *)pSource;
        pListener->m_nPriority = priority;
        pListener->m_pDispatcher = this;
        pListener->m_flag = flag;
        return true;
    }
    return false;
}

//移除监听器
void SDispatcher::RemoveEventListener(const SEventListener *pListener,bool bRelease)
{
    if(pListener)
    {
        auto type = pListener->GetType();
        auto &it = m_pListenerMap->find(type);
        if( it != m_pListenerMap->end())
        {
            auto list = it->second;
            for( auto itListener = list->begin() ;itListener != list->end();++itListener)
            {
                if((*itListener) == pListener)
                {
                    (*itListener)->m_pDispatcher = nullptr;
                    if(bRelease)delete (*itListener);
                    list->erase(itListener);
                    break;
                }
            }
        }
    }
}
void SDispatcher::RemoveAllEventListenersByType(SEvent::Type type,bool bRelease)
{
    auto &it = m_pListenerMap->find(type);
    if( it != m_pListenerMap->end())
    {
        auto list = it->second;
        for( auto itListener = list->begin() ;itListener != list->end();)
        {
            (*itListener)->m_pDispatcher = nullptr;
            if(bRelease)delete (*itListener);
            list->erase(itListener++);
        }
        delete list;
        m_pListenerMap->erase(it);
    }
}
//清空所有监听者
void SDispatcher::RemoveAllEventListeners(bool bRelease)
{
    for( auto &it = m_pListenerMap->begin() ; it !=m_pListenerMap->end() ;++it)
    {
        auto list = it->second;
        for( auto itListener = list->begin() ;itListener != list->end();)
        {
            (*itListener)->m_pDispatcher = nullptr;
            if(bRelease)delete (*itListener);
            list->erase(itListener++);
        }
        delete list;
        m_pListenerMap->erase(it);
    }
    m_pListenerMap->clear();
}

//取得事件
bool SDispatcher::PeekEvent(SEvent *&pOutEvent, unsigned int peekflag) const
{
    if (!m_pEventQueue->empty())
    {
        pOutEvent=m_pEventQueue->top();
        m_pEventQueue->pop();
        pOutEvent->m_bIsAdded = false;
        return true;
    }
    pOutEvent = nullptr;
    return false;
}

void SDispatcher::_HandleEvent(SEvent *&pEvent)
{
    if (pEvent) 
    {
        _DoDealEvent(pEvent);
        _DoPurgeEvent(pEvent);
    }
}

//处理事件
void SDispatcher::_DoDealEvent(SEvent *&pEvent)
{
    //事件处理中
    _OnDealingEvent(pEvent);

}
void SDispatcher::_DoPurgeEvent(SEvent *&pEvent)
{
    //事件处理后
    _OnAftDealingEvent(pEvent);
}
//处理队列事件
void SDispatcher::DealAllEvents(unsigned int dealflag)
{
    SEvent *pOutEvent = nullptr;
    while (PeekEvent(pOutEvent, dealflag))
    {
        if (SEventFlag::HaveFlag(pOutEvent->m_flag,SEventFlag::Unblock))
            DispatchEvent(pOutEvent, pOutEvent->m_flag);
        else
            SendEvent(pOutEvent, pOutEvent->m_flag);
    }
}

//移除队列事件
void SDispatcher::ClearAllEvents(bool bRelease)
{
    SEvent *pOutEvent = nullptr;
    while(PeekEvent(pOutEvent))
    {
        if(bRelease) delete pOutEvent; 
    }
}

//事件处理-数值越低,优先级越高
void SDispatcher::PushEvent(SEvent *pEvent, int priority, unsigned int flag)
{
    pEvent->m_flag = flag;
    pEvent->m_nPriority = priority;
    pEvent->m_bIsAdded = true;
    m_pEventQueue->push(pEvent);
}
void SDispatcher::PushEvent(SEvent *pEvent, unsigned int flag)
{
    PushEvent(pEvent, SDispatcher::MINPRIORITY, flag);
}

//发送事件-立即发送
void SDispatcher::SendEvent(SEvent *pEvent, unsigned int flag)
{
    pEvent->m_flag = flag;
    _HandleEvent(pEvent);
}

//分发事件-异步
void SDispatcher::DispatchEvent(SEvent *pEvent, unsigned int flag)
{
    //子线程分离后会自行消亡
    pEvent->m_flag = flag;
    std::thread t([=](){
        SDispatcher::_OnThreadHandleEvent(pEvent);
    });
    t.detach();
}

///////
//插入链表
void SDispatcher::_InsertList(int weight,SEventListener *&pListener)
{
    const SEvent::Type &type = pListener->m_type;
    auto itList = m_pListenerMap->find(type);
    std::list<SEventListener *> *pList = nullptr;
    if(itList == m_pListenerMap->end())
    {
        pList = new std::list<SEventListener *>();
        m_pListenerMap->insert(std::pair<SEvent::Type,std::list<SEventListener *>*>(type,pList));
    }else{
        pList = itList->second;
    }
    auto &it = pList->begin();
    for (it = pList->begin(); it != pList->end(); ++it)
    {
        if (weight < (*it)->GetPriority())
        {
            pList->insert(it, pListener);
            return;
        }
    }
    pList->push_back(pListener);
}
//调整事件
void SDispatcher::_DirtyEvent(unsigned int flag,SEvent *&pEvent)
{
    m_pushEventMutex.lock();
    m_pqueDirtyEvents->push(std::pair<unsigned int ,SEvent *>(flag,pEvent));
    m_pushEventMutex.unlock();
}

//检查事件
void SDispatcher::_CheckEvent(SEvent *&pEvent)
{
    //判断是否是自消亡
    if (SEventFlag::HaveFlag(pEvent->m_flag,SEventFlag::AutoRelease))
        _DirtyEvent(pEvent->m_flag,pEvent);
}

void SDispatcher::_DirtyEventHandle(unsigned int flag,SEvent *pEvent)
{
    if (SEventFlag::HaveFlag(flag,SEventFlag::AutoRelease))
    {
        if (SEventFlag::HaveFlag(flag, SEventFlag::BindUserData))
        {
            if (pEvent->m_pUserData)
                delete pEvent->m_pUserData;
        }
        delete pEvent;
    }
    

}

//调整事件监听者
void SDispatcher::_DirtyListener(unsigned int flag,SEventListener *pListener)
{
    m_pushListenerMutex.lock();
    m_pqueDirtyListeners->push(std::pair<unsigned int ,SEventListener *>((unsigned int)flag,pListener));
    m_pushListenerMutex.unlock();
}
//检查事件
void SDispatcher::_CheckListener(SEventListener *&pListener)
{
     //判断是否为重排
    if (SEventFlag::HaveFlag(pListener->m_flag,SEventFlag::ReOrder))
        _DirtyListener((unsigned int)SEventFlag::ReOrder,pListener);

}

void SDispatcher::_DirtyListenerHandle(unsigned int flag,SEventListener *pListener)
{
    if (SEventFlag::HaveFlag(flag,SEventFlag::ReOrder))       //重排事件
    {
        SEventFlag::RemoveFlag(pListener->m_flag,SEventFlag::ReOrder);
        RemoveEventListener(pListener);
        AddEventListenerWithFixedPriority(pListener, pListener->m_pSource, pListener->m_nPriority,pListener->m_flag);
    }
    if (SEventFlag::HaveFlag(flag,SEventFlag::Remove))       //重排事件
    {
        SEventFlag::RemoveFlag(pListener->m_flag,SEventFlag::Remove);
        RemoveEventListener(pListener);
    }
    if (SEventFlag::HaveFlag(flag,SEventFlag::Delete))       //重排事件
    {
        SEventFlag::RemoveFlag(pListener->m_flag,SEventFlag::Delete);
        RemoveEventListener(pListener,true);
    }
}

//事件处理中
void SDispatcher::_OnDealingEvent(SEvent *&pEvent)
{
    auto &it = m_pListenerMap->find(pEvent->GetType());
    if( it != m_pListenerMap->end())
    {
        std::list<SEventListener *> *pList = it->second;
        for( auto &pListener : *pList)
        {
            if(!SEventFlag::HaveFlag(pEvent->m_flag,SEventFlag::OnceDelivery))
            {
                pListener->OnHandle(pEvent);
                _CheckListener(pListener);
            }
            else break;
        }
    }else{
        //垃圾事件操作
    }
    _CheckEvent(pEvent);

}

//事件处理后
void SDispatcher::_OnAftDealingEvent(SEvent *&pEvent)
{
    //线程加锁-读取的时候不能进行写操作,但可以多个线程读取
    //事件的善后处理
    m_pushEventMutex.lock();
    {
        std::pair<unsigned int ,SEvent *> eventPair;
        while(!m_pqueDirtyEvents->empty())
        {
            eventPair = m_pqueDirtyEvents->front();
            _DirtyEventHandle(eventPair.first,eventPair.second);

            m_pqueDirtyEvents->pop();

        }
    }
    m_pushEventMutex.unlock();

    //监听器的善后处理
    m_pushListenerMutex.lock();
    {
        std::pair<unsigned int ,SEventListener *> listenerPair;
        while(!m_pqueDirtyListeners->empty())
        {
            listenerPair = m_pqueDirtyListeners->front();
            _DirtyListenerHandle(listenerPair.first,listenerPair.second);
           
            m_pqueDirtyListeners->pop();
            
        }
    }
    m_pushListenerMutex.unlock();
    
}

void SDispatcher::_OnThreadHandleEvent(SEvent *pEvent)
{
    //没有必要交给主线程处理,否则需要考虑队列的线程安全
    _HandleEvent(pEvent);

    //可能会引发Map的线程安全
//     auto &it = m_pListenerMap->find(pEvent->GetType());
//     if( it != m_pListenerMap->end())
//     {
//         std::list<SEventListener *> *pList = it->second;
//         for( auto &pListener : *pList)
//         {
//             if(!SEventFlag::HaveFlag(pEvent->m_flag,SEventFlag::OnceDelivery))
//             {
//                 pListener->OnHandle(pEvent);
//                 _DirtyListenerHandle(pListener->m_flag,pListener);
//             }
//             else break;
//         }
        
//     }else
//     {
//         //垃圾事件操作
//     }
//    _DirtyEventHandle(pEvent->m_flag,pEvent);
}
























