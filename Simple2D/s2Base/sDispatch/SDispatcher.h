/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-03-27 10:15:23
 * @Brief: 事件分发器(事件源)-用来分发事件的(Event) 
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-17 11:22:38
 * @Last Modified log: 
 */

#ifndef _SDISPATCHER_H_
#define _SDISPATCHER_H_

#include <list>
#include <queue>
#include <unordered_map>
#include <mutex>
#include "SEvent.h"
#include "SEventListener.h"
#include "SEventFlag.h"

class SDispatcher
{
    struct EventCmp
    {
        bool operator()(const SEvent *e1,const SEvent *e2)
        {
            return e1->m_nPriority < e2->m_nPriority;
        }
    };
public:
    static const int MINPRIORITY = 2147483647; //最小优先级
public:
    SDispatcher();
    virtual ~SDispatcher();
public:
    //添加监听器
    virtual bool AddEventListener(SEventListener *pListener, unsigned int flag = 0);
    virtual bool AddEventListener(SEventListener *pListener, const void *pSource, unsigned int flag = 0);
    //以优先级添加监听器
    virtual bool AddEventListenerWithFixedPriority(SEventListener *pListener, unsigned int flag = 0);
    virtual bool AddEventListenerWithFixedPriority(SEventListener *pListener, const void *pSource, int priority = MINPRIORITY, unsigned int flag = 0);
    //移除监听器
    virtual void RemoveEventListener(const SEventListener *pListener,bool bRelease = false);
    //清空某类所有监听者
    virtual void RemoveAllEventListenersByType(SEvent::Type type,bool bRelease = false);
    //清空所有监听者
    virtual void RemoveAllEventListeners(bool bRelease = false);

public:
    //取得事件
    virtual bool PeekEvent(SEvent *&pOutEvent, unsigned int peekflag = 0) const;
    //处理队列事件
    virtual void DealAllEvents(unsigned int dealflag = 0);
    //移除所有事件
    virtual void ClearAllEvents(bool bRelease = false);
    //事件处理-数值越低,优先级越高
    virtual void PushEvent(SEvent *pEvent, int priority , unsigned int flag = 0);
    virtual void PushEvent(SEvent *pEvent, unsigned int flag = 0);
    //发送事件-立即发送
    virtual void SendEvent(SEvent *pEvent, unsigned int flag = 0);
    //分发事件-异步
    virtual void DispatchEvent(SEvent *pEvent, unsigned int flag = 0);
    
protected:
    //处理事件
    virtual void _HandleEvent(SEvent *&pEvent);
    virtual void _DoDealEvent(SEvent *&pEvent);
    virtual void _DoPurgeEvent(SEvent *&pEvent);

    //插入链表
    void _InsertList(int weight,SEventListener *&pListener);
    //调整事件监听者
    void _DirtyEvent(unsigned int flag,SEvent *&pEvent);
    //检查事件
    void _CheckEvent(SEvent *&pEvent);
    //脏事件处理
    void _DirtyEventHandle(unsigned int flag,SEvent *pEvent);

    //调整事件监听者
    void _DirtyListener(unsigned int flag,SEventListener *pListener);
    //检查事件
    void _CheckListener(SEventListener *&pListener);
    //脏监听器处理
    void _DirtyListenerHandle(unsigned int flag,SEventListener *pListener);
    

    //事件处理中
    void _OnDealingEvent(SEvent *&pEvent);
    //事件处理后
    void _OnAftDealingEvent(SEvent *&pEvent);
    
    //线程运行的事件处理
    void _OnThreadHandleEvent(SEvent *pEvent);

private:
    std::unordered_map<SEvent::Type,std::list<SEventListener *>*>                 *m_pListenerMap;          //事件监听函数
    std::priority_queue<SEvent *,std::vector<SEvent *>,EventCmp>                  *m_pEventQueue;           //事件队列
    
    std::queue<std::pair<unsigned int ,SEvent *> >                                *m_pqueDirtyEvents;       //事件脏标记
    std::queue<std::pair<unsigned int ,SEventListener *> >                        *m_pqueDirtyListeners;    //监听器脏标记

    std::mutex                                                                     m_pushEventMutex;         //线程互斥对象-读写锁
    std::mutex                                                                     m_pushListenerMutex;      //线程互斥对象-读写锁
};
#endif
