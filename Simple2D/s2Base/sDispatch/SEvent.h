/**
*    SEvent
*    @brief 可重载事件
*    @author cnscj
*    @link -
*    @version v1.0
*    @date 27/03/2018
*    @update 27/03/2018
*/

#ifndef _SEVENT_H_
#define _SEVENT_H_

class SEvent
{
    friend class SDispatcher;
public:
    typedef unsigned int Type;
public:
    //取得事件类型
    virtual SEvent::Type GetType()const;
    virtual bool SetType(SEvent::Type type); //事件发送完毕无法更改
    //取得事件源
    virtual void *GetSender()const;
    virtual bool SetSender(void *pSender);
    //事件优先级
    virtual int GetPriority()const;
    virtual bool SetPriority(int nPriority);
    //事件能否往下传递
    virtual bool GetDelivery()const;
    virtual void SetDelivery(bool bDelivery);
    //取得自定义数据,绑定数据以自释放
    virtual void SetUserData(const void *pUserData,bool bBind = false);
    virtual void *GetUserData() const;

    //自释放
    virtual SEvent *AutoRelease(bool bRelease=true);
public:
    SEvent(SEvent::Type type, void *pSender = nullptr,void *pUserData = nullptr);
    virtual ~SEvent();
private:
    SEvent::Type         m_unType;                 //事件类型
    void                *m_pSender;                 //事件来源(事件产生者)

    void                *m_pUserData;               //用户数据
private:
    //
    int                 m_nPriority;                //优先级
    unsigned int        m_flag;                     //事件的标志
    bool                m_bIsAdded;                 //是否被添加到队列

};
#endif
