/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-18 18:49:51 
 * @Brief: 纹理池
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-19 15:46:44
 * @Last Modified log: 
 */
#ifndef _S2TEXTUREPOOL_H_
#define _S2TEXTUREPOOL_H_
#include "../s2Base/sMemory/SReferencePool.hpp"
#include "../s2Base/sLang/SValue.h"
#include "../s2Core/S2Singleton.hpp"
class S2Renderer;
class S2Texture;
class S2TexturePool : public S2Singleton<S2TexturePool>
{
public:
    S2TexturePool();
    ~S2TexturePool();
public:
    //从文件中创建纹理
    S2Texture *CreateWithFile(S2Renderer *pRenderer, S2String strFile);
    //从资源中创建纹理
    S2Texture *CreateWithResource(S2Renderer *pRenderer, S2uInt unRcid);
    //从内存中加载纹理
    S2Texture *CreateWithMemory(S2Renderer *pRenderer, const S2Data pAddr, S2uInt len);

    //维持引用
    void Retain(S2Texture *pTexture);
    //从池中释放
    void Release(S2Texture *pTexture);
    //取得引用次数
    S2uInt GetRefCount(S2Texture *pTexture);
private:
    //取得Md5Key
    S2String GetMd5Key(SValue key);
private:
    SReferencePool<S2String, S2Texture> m_mapTextures;              //保存从文件中加载的纹理

};
#endif