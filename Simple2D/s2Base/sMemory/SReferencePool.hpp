/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-18 19:46:47 
 * @Brief: 引用对象池
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-17 11:32:00
 * @Last Modified log: 
 */
#ifndef _SREFPOOL_H_
#define _SREFPOOL_H_
#include <functional>
#include <unordered_map>
#include "SPool.h"
template <class K, class V>
class SReferencePool : public SPool
{
public:
    //创建对象
    V *Create(K key, std::function<V *()> newer = [](){V *p = new V(); return p; }, bool bRetain = false);
    //维持引用
    void Retain(V *pObject);
    void Retain(K key);
    //释放对象
    void Release(V *pObject,std::function<void(V *)> releaser = [](V *pObject){delete pObject;});
    void Release(K key,std::function<void(V *)> releaser = [](V *pObject){delete pObject;});
    //释放所有对象
    void ReleaseAll(std::function<void(V *)> releaser = [](V *pObject){delete pObject;});

    //取得引用次数
    unsigned int GetRefCount(V *pObject);
    unsigned int GetRefCount(K key);
    //清空
    void Clear();
private:
    typedef struct tagref_info
    {
        unsigned int unRefCount;      //引用次数
        K            tKey;            //Key
        V            *pObject;        //引用指针
    }Ref_Info;
    typedef typename std::unordered_map<V *, Ref_Info>::iterator iterator;
    bool GetInfoByValue(V *pObject, iterator *pOut);
    bool GetInfoByKey(K key, iterator *pOut);
private:
    std::unordered_map<V *,Ref_Info> m_mapRefPool;
    std::unordered_map<K, V *> m_mapKV;
};

//创建对象
template <class K, class V>
V *SReferencePool<K, V>::Create(K key, std::function<V *()> newer, bool bRetain)
{
    iterator it;
    if (!GetInfoByKey(key, &it))
    {
        V *pObject = newer();
        if (pObject)
        {
            Ref_Info info;
            info.unRefCount = 1;
            info.tKey = key;
            info.pObject = pObject;

            m_mapRefPool.insert(std::pair<V *, Ref_Info>(pObject, info));
            m_mapKV.insert(std::pair<K, V *>(key, pObject));
        }
        return pObject;
    }else{
        if (bRetain)
            it->second.unRefCount++;
        return it->second.pObject;
    }
}
//增加引用
template <class K, class V>
void SReferencePool<K, V>::Retain(V *pObject)
{
    iterator it;
    if (GetInfoByValue(pObject,&it))
    {
        it->second.unRefCount++;
    }
}

template <class K, class V>
void SReferencePool<K, V>::Retain(K key)
{
    iterator it;
    if (GetInfoByKey(key, &it))
    {
        ++it->second.unRefCount;
    }
}

//释放对象
template <class K, class V>
void SReferencePool<K,V>::Release(V *pObject,std::function<void(V *pObject)> releaser)
{
    iterator it;
    if (GetInfoByValue(pObject, &it))
    {
        --it->second.unRefCount;
        if (it->second.unRefCount <= 0)
        {
            m_mapKV.erase(it->second.tKey);
            releaser(it->second.pObject);
            m_mapRefPool.erase(it);
        }
    }
    else releaser(pObject);
}
template <class K, class V>
void SReferencePool<K,V>::Release(K key,std::function<void(V *pObject)> releaser)
{
    iterator it;
    if (GetInfoByKey(key, &it))
    {
        --it->second.unRefCount;
        if(it->second.unRefCount <= 0)
        {
            m_mapKV.erase(it->second.tKey);
            releaser(it->second.pObject);
            m_mapRefPool.erase(it);
            
        }
    }   
}

//取得引用次数
template <class K, class V>
unsigned int SReferencePool<K, V>::GetRefCount(V *pObject)
{
    iterator it;
    if (GetInfoByValue(pObject, &it))
    {
        return it->second.unRefCount;
    }else return 0;

}
template <class K, class V>
unsigned int SReferencePool<K, V>::GetRefCount(K key)
{
    iterator it;
    if (GetInfoByKey(key, &it))
    {
        return it->second.unRefCount;
    }else return 0;
        
}


template <class K, class V>
void SReferencePool<K,V>::ReleaseAll(std::function<void(V *)> releaser)
{
    for (auto &it = m_mapRefPool.begin(); it!= m_mapRefPool.end();)
    {
        releaser(it->second.pObject);
        m_mapRefPool.erase(it++);
    }
    m_mapKV.clear();
}
template <class K, class V>
void SReferencePool<K,V>::Clear()
{
    m_mapRefPool.clear();
    m_mapKV.clear();
}

template <class K, class V>
bool SReferencePool<K, V>::GetInfoByValue(V *pObject, iterator *pOut)
{
    iterator &it = m_mapRefPool.find(pObject);
    if (it != m_mapRefPool.end())
    {
        if (pOut)*pOut = it;
        return true;
    }
    
    return false;
}
template <class K, class V>
bool SReferencePool<K, V>::GetInfoByKey(K key, iterator *pOut)
{
    /*
    iterator it = m_mapRefPool.begin();
    for (; it != m_mapRefPool.end(); ++it)
    {
        if (it->second.tKey == key)
        {
            if (pOut)*pOut = it;
            return true;
        }
    }

    return false;
    */
    auto &it = m_mapKV.find(key);
    if (it != m_mapKV.end())
    {
        return GetInfoByValue(it->second, pOut);
    }
    return false;
}
#endif

