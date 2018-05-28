/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2017-08-30 00:00:00
 * @Brief: 纹理缓存类-缓存纹理对象
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-19 15:48:04
 * @Last Modified log: 
 */

#ifndef _S2TEXTURECACHE_H_
#define _S2TEXTURECACHE_H_
#include "../s2Base/sLang/SValue.h"
#include "../s2Core/S2Singleton.hpp"
class S2Texture;
class S2TextureCache : public S2Singleton<S2TextureCache>
{
public:
	S2TextureCache();
	virtual ~S2TextureCache();
public:
	//从自定义别名中取得纹理
	bool AddTexture(S2String szKeyName, S2Texture *pTexture);
    //取得纹理
	S2Texture *GetTexture(S2String strKeyName);
    //移除纹理
	void RemoveTexture(S2String strKeyName, bool bRelease = false);
public:
    //从文件中创建纹理
    S2Texture *CreateWithFile(S2String strFile);
    //从资源中创建纹理
    S2Texture *CreateWithResource(S2uInt unRcid);
    //从内存中加载纹理
    S2Texture *CreateWithMemory(const S2Data pAddr, S2uInt len);

    //释放
    bool Release(S2Texture *pTexture);

    //清理所有引用次数为1的对象
    void Purge();
private:
    //取得Md5Key
    S2String GetMd5Key(SValue key);
private:
    S2Map<S2String, S2Texture *> m_mapTextures;              //保存从文件中加载的纹理

};
#endif