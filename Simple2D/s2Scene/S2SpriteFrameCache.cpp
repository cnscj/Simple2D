/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-17 09:17:39 
 * @Brief: 
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-22 13:59:41
 * @Last Modified log: 
 */
#include "../s2Base/sParse/SMD5.h"
#include "S2SpriteFrameCache.h"
#include "S2SpriteFrame.h"
#include "S2TextureCache.h"

S2SpriteFrameCache::S2SpriteFrameCache()
{

}
S2SpriteFrameCache::~S2SpriteFrameCache()
{
    for (auto &it = m_mapSpriteFrames.begin(); it != m_mapSpriteFrames.end() ; ++it)
    {
        S2SAFERELEASE(it->second);
        m_mapSpriteFrames.erase(it);
    }
}

//添加精灵帧
bool S2SpriteFrameCache::AddSpriteFrame(S2String strKeyName,S2SpriteFrame *pFrame)
{
    bool res = m_mapSpriteFrames.insert(S2Pair<S2String, S2SpriteFrame *>(GetMd5Key(SValue("K:%s", strKeyName.c_str())), pFrame)).second;
    if (res)pFrame->Retain();
    return res;
}
//移除精灵帧
void S2SpriteFrameCache::RemoveSpriteFrame(S2String strKeyName,bool bRelease)
{
    auto &it = m_mapSpriteFrames.find(GetMd5Key(SValue("K:%s", strKeyName.c_str())));
    if (it != m_mapSpriteFrames.end())
    {
        if(bRelease)
            S2SAFERELEASE(it->second);
        m_mapSpriteFrames.erase(it);
    }
}
//取得精灵帧
S2SpriteFrame *S2SpriteFrameCache::GetSpriteFrame(S2String strKeyName)
{
    auto &it = m_mapSpriteFrames.find(GetMd5Key(SValue("K:%s", strKeyName.c_str())));
    if (it != m_mapSpriteFrames.end()){
        return it->second;
    }
    return nullptr;
}

S2SpriteFrame *S2SpriteFrameCache::CreateWithTexture(S2Texture *pTexture, const S2Rect *rt)
{
    if (pTexture)
    {
        S2String key;
        if (rt)
            key = GetMd5Key(SValue("T:%ld-%d%d%d%d", (void *)pTexture, rt->left, rt->top, rt->right, rt->bottom));
        else
            key = GetMd5Key(SValue("T:%ld", (void *)pTexture));

        auto &it = m_mapSpriteFrames.find(key);
        if (it == m_mapSpriteFrames.end())
        {
            auto pSpriteFrame = S2Object::Create<S2SpriteFrame>();
            pSpriteFrame->CreateWithTexture(pTexture, rt);
            pSpriteFrame->Retain();
            m_mapSpriteFrames.insert(S2Pair<S2String, S2SpriteFrame *>(key, pSpriteFrame));
            return pSpriteFrame;
        }
        return it->second;
    }
    return nullptr;
}
S2SpriteFrame *S2SpriteFrameCache::CreateWithFile(S2String strFile, const S2Rect *rt)
{
    auto pTexture = S2TextureCache::GetInstance()->CreateWithFile(strFile);

    return CreateWithTexture(pTexture, rt);
}
S2SpriteFrame *S2SpriteFrameCache::CreateWithResource(S2uInt unRcid, const S2Rect *rt)
{
    auto pTexture = S2TextureCache::GetInstance()->CreateWithResource(unRcid);

    return CreateWithTexture(pTexture, rt);
}
S2SpriteFrame *S2SpriteFrameCache::CreateWithMemory(const S2Data pAddr, S2uInt len, const S2Rect *rt)
{
    auto pTexture = S2TextureCache::GetInstance()->CreateWithMemory(pAddr,len);

    return CreateWithTexture(pTexture, rt);
}

bool S2SpriteFrameCache::Release(S2SpriteFrame *pSpriteFrame)
{
    auto &it = m_mapSpriteFrames.begin();
    for (; it != m_mapSpriteFrames.end();)
    {
        if (it->second == pSpriteFrame)
        {
            it->second->Release();
            m_mapSpriteFrames.erase(it++);
            return true;
        }
        else ++it;
    }
    return false;
}

void S2SpriteFrameCache::Purge()
{
    for (auto &it = m_mapSpriteFrames.begin(); it != m_mapSpriteFrames.end();)
    {
        if (it->second->GetRefCount() <= 1)
        {
            it->second->Release();
            m_mapSpriteFrames.erase(it++);
        }
        else ++it;
    }
}

S2String S2SpriteFrameCache::GetMd5Key(SValue key)
{
    return SMD5(key.ToString()).ToStr();
}