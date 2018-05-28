#include "S2Object.h"

S2uInt S2Object::sm_unObjectCount = 0;
///
S2Object::S2Object()
:m_unId(++sm_unObjectCount)
, m_nTag(-1), m_unFlag(FLAG_NONE)
{
    
}
S2Object::~S2Object()
{

}


//为对象设置标记
S2Int S2Object::GetTag()const
{
    return m_nTag;
}
void S2Object::SetTag(S2Int tag)
{
    m_nTag = tag;
}

//取得对象ID
S2uInt S2Object::GetId() const
{
    return m_unId;
}

void S2Object::SetFlag(S2uInt flag)
{
    m_unFlag = flag;
}
void S2Object::ChangeFlag(S2uInt flag, bool bState)
{
    if (bState)
    {
        m_unFlag = m_unFlag | flag;
    }
    else
    {
        m_unFlag = m_unFlag & ~flag;
    }
}

S2uInt S2Object::GetFlag()const
{
    return m_unFlag;
}


//初始化化
bool S2Object::Init()
{
    return true;
}

//比较函数
bool S2Object::Compare(S2Object *pObject)
{
    return this > pObject;
}

//转化为字符串
S2String S2Object::ToString()
{
    //TODO:
    return "";
}
