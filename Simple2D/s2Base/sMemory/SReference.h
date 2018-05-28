/**
*    SReference
*    @brief 引用接口类
*    @author ZEROX
*    @link -
*    @version v1.1
*    @date 11/18/2017
*    @update 11/18/2017
*/
#ifndef _SREFERENCE_H_
#define _SREFERENCE_H_
//
//#define CREATE_FUNC(__TYPE__) \
//    static __TYPE__* Create() \
//{ \
//    __TYPE__ *pRet = new __TYPE__(); \
//if (pRet && pRet->Init()) \
//    { \
//    pRet->AutoRelease(); \
//    return pRet; \
//    } \
//    else \
//    { \
//    delete pRet; \
//    pRet = nullptr; \
//    return nullptr; \
//    } \
//}

class SReference
{
    friend class SAutoReleasePool;
public:
    //创建对象
    template<class T,class... _Args>
    static T *Create(_Args &&... __Ax)
    {
        T *pObj = new T(/*std::forward<_Args>*/(__Ax)...);
        if (pObj && pObj->Init())
        {
            pObj->AutoRelease();
            return pObj;
        }
        else
        {
            delete pObj;
            pObj = nullptr;
            return nullptr;
        } 
    }
public:
    //初始化
    virtual bool Init();

    //自动释放-否则只能手动释放
    virtual void AutoRelease();

    //取消自动释放
    virtual void CancelAutoRelease();

    //释放对象(引用自减)
    virtual void Release();
    //稍后释放对象
    virtual void ReleaseLater();
    //引用持有(引用自增)
    virtual void Retain();
public:
    //返回引用次数
    virtual unsigned int GetRefCount();

    //是否为自释放
    virtual bool IsAutoRelease();

    //是否为单引用
    virtual bool IsSingleRefrence();
private:
    unsigned int    m_unRefCount;           //引用次数

    unsigned int    m_unManagedCount;       //自释放次数
protected:
    SReference();
    SReference(const SReference *pRef);
    virtual ~SReference();
};
#endif