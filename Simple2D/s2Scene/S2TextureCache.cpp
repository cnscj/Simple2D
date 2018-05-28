/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-17 09:25:33 
 * @Brief: 
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-18 20:40:36
 * @Last Modified log: 
 */
#include "../s2Base/sParse/SMD5.h"
#include "../s2Render/S2Texture.h"
#include "S2TextureCache.h"
#include "S2Director.h"

S2TextureCache::S2TextureCache()
{
    
}
S2TextureCache::~S2TextureCache()
{

}

//从自定义别名中取得纹理
bool S2TextureCache::AddTexture(S2String strKeyName, S2Texture *pTexture)
{
    if (pTexture)
    {
        bool ret = m_mapTextures.insert(S2Pair<S2String, S2Texture *>(GetMd5Key(SValue("K:%s", strKeyName.c_str())), pTexture)).second;
        if (ret)pTexture->Retain();
        return ret;
    }
    return false;
}
//取得纹理
S2Texture *S2TextureCache::GetTexture(S2String strKeyName)
{
    auto &it = m_mapTextures.find(GetMd5Key(SValue("K:%s", strKeyName.c_str())));
    if (it != m_mapTextures.end()){
        return it->second;
    }
    return nullptr;
}
//移除纹理
void S2TextureCache::RemoveTexture(S2String strKeyName, bool bRelease)
{
    auto &it = m_mapTextures.find(GetMd5Key(SValue("K:%s", strKeyName.c_str())));
    if (it != m_mapTextures.end())
    {
        if(bRelease)
            it->second->Release();
        m_mapTextures.erase(it);
    }
}

//从文件中创建纹理
S2Texture *S2TextureCache::CreateWithFile(S2String strFile)
{
    S2String key = GetMd5Key(SValue("F:%s", strFile.c_str()));
    auto &it = m_mapTextures.find(key);
    if( it == m_mapTextures.end() )
    {
        auto pTexture = (S2Texture *)S2Director::GetInstance()->GetRenderView()->GetViewRenderer()->CreateTextureWithFile(strFile);
        pTexture->Retain();
        m_mapTextures.insert(S2Pair<S2String,S2Texture *>(key,pTexture));
        return pTexture;
    }
    return it->second;
}

//从资源中创建纹理
S2Texture *S2TextureCache::CreateWithResource(S2uInt unRcid)
{
    S2String key = GetMd5Key(SValue("R:%d", unRcid));
    auto &it = m_mapTextures.find(key);
    if( it == m_mapTextures.end() )
    {
        auto pTexture = (S2Texture *)S2Director::GetInstance()->GetRenderView()->GetViewRenderer()->CreateTextureWithResource(unRcid);
        pTexture->Retain();
        m_mapTextures.insert(S2Pair<S2String,S2Texture *>(key,pTexture));
        return pTexture;
    }
    return it->second;
}
//从内存中加载纹理
S2Texture *S2TextureCache::CreateWithMemory(const S2Data pAddr,S2uInt len)
{
    S2String key=GetMd5Key(SValue("M:%ld-%d",pAddr,len));
    auto &it = m_mapTextures.find(key);
    if( it == m_mapTextures.end() )
    {
        auto pTexture = (S2Texture *)S2Director::GetInstance()->GetRenderView()->GetViewRenderer()->CreateTextureWithMemory(pAddr, len);
        pTexture->Retain();
        m_mapTextures.insert(S2Pair<S2String,S2Texture *>(key,pTexture));
        return pTexture;
    }
    return it->second;
}

//释放
bool S2TextureCache::Release(S2Texture *pTexture)
{
    auto &it = m_mapTextures.begin();
    for (; it != m_mapTextures.end();)
    {
        if (it->second == pTexture)
        {
            it->second->Release();
            m_mapTextures.erase(it++);
            return true;
        }
        else ++it;
    }
    return false;
}

void S2TextureCache::Purge()
{
    for (auto &it = m_mapTextures.begin(); it != m_mapTextures.end();)
    {
        if (it->second->GetRefCount() <= 1)
        {
            it->second->Release();
            m_mapTextures.erase(it++);
        }
        else ++it;
    }
}

S2String S2TextureCache::GetMd5Key(SValue key)
{
    return SMD5(key.ToString()).ToStr();
}