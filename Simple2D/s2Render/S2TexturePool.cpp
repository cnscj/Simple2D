/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-18 20:30:59 
 * @Brief: 纹理对象池
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-22 14:00:59
 * @Last Modified log: 
 */

#include "../s2Base/sParse/SMD5.h"
#include "S2TexturePool.h"
#include "S2Renderer.h"
#include "S2Texture.h"
S2TexturePool::S2TexturePool()
{
    
}
S2TexturePool::~S2TexturePool()
{
    m_mapTextures.ReleaseAll([](S2Texture *pTexture){
        S2SAFERELEASE(pTexture);
    });
}

//从文件中创建纹理
S2Texture *S2TexturePool::CreateWithFile(S2Renderer *pRenderer, S2String strFile)
{
    S2String key = GetMd5Key(SValue("F:%s", strFile.c_str()));
    return m_mapTextures.Create(key,[=](){
        auto pTexture = S2Object::Create<S2Texture>();
        pTexture->CreateWithFile(pRenderer, strFile);
        return pTexture;
    });
}

//从资源中创建纹理
S2Texture *S2TexturePool::CreateWithResource(S2Renderer *pRenderer, S2uInt unRcid)
{
    S2String key = GetMd5Key(SValue("R:%d", unRcid));
    return m_mapTextures.Create(key,[=](){
        auto pTexture = S2Object::Create<S2Texture>();
        pTexture->CreateWithResource(pRenderer, unRcid);
        return pTexture;
    });
}
//从内存中加载纹理
S2Texture *S2TexturePool::CreateWithMemory(S2Renderer *pRenderer, const S2Data pAddr, S2uInt len)
{
    S2String key=GetMd5Key(SValue("M:%ld-%d",pAddr,len));
    return m_mapTextures.Create(key,[=](){
        auto pTexture = S2Object::Create<S2Texture>();
        pTexture->CreateWithMemory(pRenderer, pAddr, len);
        return pTexture;
    });
}

void S2TexturePool::Retain(S2Texture *pTexture)
{
    m_mapTextures.Retain(pTexture);
}

void S2TexturePool::Release(S2Texture *pTexture)
{
    m_mapTextures.Release(pTexture,[](S2Texture *pTexture){
        S2SAFERELEASE(pTexture);
    });
}
//取得引用次数
S2uInt S2TexturePool::GetRefCount(S2Texture *pTexture)
{
    return m_mapTextures.GetRefCount(pTexture);
}

S2String S2TexturePool::GetMd5Key(SValue key)
{
    return SMD5(key.ToString()).ToStr();
}