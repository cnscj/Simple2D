#include "SWrapper.h"

SWrapper::SWrapper()
{

}
SWrapper::~SWrapper()
{

}

void SWrapper::Add(std::string key, void *value, bool bBind)
{
    auto it = m_objectsMap.find(key);
    auto pObject = new SConverer(value);
    ElementInfo info;
    info.unFlag = bBind ? 1 : 0;
    info.pObject = pObject;
    if (it != m_objectsMap.end())
    {
        OnHandle(it->second);
        it->second = info;
    }
    else
    {
        m_objectsMap.insert(std::pair<std::string, ElementInfo>(key, info));
    }

}
void SWrapper::Remove(std::string key)
{
    auto it = m_objectsMap.find(key);
    if (it != m_objectsMap.end())
    {
        OnHandle(it->second);
        m_objectsMap.erase(it);
    }
}
void SWrapper::RemoveAll()
{
    for (auto it = m_objectsMap.begin(); it != m_objectsMap.end();)
    {
        OnHandle(it->second);
        m_objectsMap.erase(it++);
    }
}

void SWrapper::OnHandle(const ElementInfo &info)
{
    if (info.unFlag == 1)
    {
        delete info.pObject->Get();
        delete info.pObject;
    }
}
SConverer *SWrapper::Get(std::string key)
{
    auto it = m_objectsMap.find(key);
    if (it != m_objectsMap.end())
    {
        return it->second.pObject;
    }
    return nullptr;
}

SConverer *SWrapper::operator[](std::string key)
{
    return Get(key);
}
