/**
*    SEventListener
*    @brief 可重载事件监听器
*    @author cnscj
*    @link -
*    @version v1.0
*    @date 27/03/2018
*    @update 27/03/2018
*/

#ifndef _SEVENTLISTENER_H_
#define _SEVENTLISTENER_H_
#include <functional>
#include "SEvent.h"
class SDispatcher;

class SEventListener
{
    friend class SDispatcher;
public:
    template <class T>
    using Handler = std::function<T>;
public:  
    SEventListener(SEvent::Type type,SEventListener::Handler<void(SEvent *)> lamdba = [](SEvent *){});
    virtual ~SEventListener();
public:
    //所注册到的事件
    virtual const SEvent::Type &GetType() const;
    virtual bool SetType(const SEvent::Type type);     //事件注册完毕无法更改
    //监听器的源
    virtual const void *GetSource() const;
    virtual bool SetSource(void *pSource);
    //取得事件分配器
    virtual const void *GetDispatcher() const;
    //设置优先级
    virtual int GetPriority() const;
    virtual void SetPriority(int nPriority);
protected:
    //处理事件接口
    virtual void OnEvent(SEvent *pEvent);
    
    //事件处理完毕
    virtual void OnFinish(SEvent *pEvent);
private:
    //消息处理
    void OnHandle(SEvent *pEvent);
protected:
    SEventListener::Handler<void(SEvent *)>     m_lamHandler;           //消息处理
private:
    SEvent::Type                        m_type;                 //监听的事件类型
    void                                *m_pSource;             //源
    SDispatcher                        *m_pDispatcher;         //分配器
    int                                 m_nPriority;            //监听优先级
    
    unsigned int                        m_flag;                 //标志
};
#endif
