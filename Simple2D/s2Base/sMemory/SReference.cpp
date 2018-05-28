#include "SReference.h"
#include "SAutoReleasePoolManager.h"

SReference::SReference()
{
    //引用次数设为1
    m_unRefCount = 1;

    //默认非自动管理
    m_unManagedCount = 0;
}
SReference::SReference(const SReference *pRef)
{
    //引用次数设为1
    m_unRefCount = 1;

    if (pRef->m_unManagedCount)
        AutoRelease();
}
SReference::~SReference()
{
    //如果接受管理,则释放时同除从管理者管理名单中移除
    //此处为手动释放时的结果
    //当次数少于0时,不在进行此项操作
    if (m_unManagedCount)
    {
        CancelAutoRelease();
    }

}

bool SReference::Init()
{
    return true;
}

//自动释放-否则只能手动释放
void SReference::AutoRelease()
{
    //调用内存管理器实例对象的AddObject函数加入当前SReference实例对象的指针
    if (!m_unManagedCount)
    {
        ReleaseLater();
    }
}

//取消自动释放
void SReference::CancelAutoRelease()
{
    SAutoReleasePoolManager::GetInstance()->RemoveObject(this);

    //自释放次数变为0为不在自释放
    m_unManagedCount = 0;
    
}

//释放对象(引用自减)
void SReference::Release()
{
    --m_unRefCount;
    //如果计数器减为0，释放本类实例化对象占用的内存  
    if (m_unRefCount <= 0)
    {
        delete this;
    }
}

//稍后释放对象
void SReference::ReleaseLater()
{
    if (m_unRefCount > m_unManagedCount)
    {
        SAutoReleasePoolManager::GetInstance()->AddObject(this);

        //打开使用内存管理器的标记  
        ++m_unManagedCount;
    }

}

//引用持有(引用自增)
void SReference::Retain()
{
    ++m_unRefCount;
}
/////////////
//返回引用次数
unsigned int SReference::GetRefCount()
{
    return m_unRefCount;
}

//是否为自释放
bool SReference::IsAutoRelease()
{
    return m_unManagedCount?true:false;
}

//是否为单引用
bool SReference::IsSingleRefrence()
{
    return m_unRefCount == 1;
}