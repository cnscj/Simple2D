/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-15 17:42:29 
 * @Brief: 精灵帧管理器
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-19 15:47:46
 * @Last Modified log: 
 */

#ifndef _S2SPRITEFRAMECACHE_H_
#define _S2SPRITEFRAMECACHE_H_
#include "../s2Base/sLang/SValue.h"
#include "../s2Core/S2Singleton.hpp"
class S2SpriteFrame;
class S2Texture;

class S2SpriteFrameCache : public S2Singleton<S2SpriteFrameCache>
{
public:
    S2SpriteFrameCache();
    ~S2SpriteFrameCache();
public:
    //添加精灵帧
    bool AddSpriteFrame(S2String strKeyName,S2SpriteFrame *pFrame);
    //移除精灵帧
    void RemoveSpriteFrame(S2String strKeyName,bool bRelease = true);
    //取得精灵帧
    S2SpriteFrame *GetSpriteFrame(S2String strKeyName);
public:
    //通过纹理创建精灵帧
    S2SpriteFrame *CreateWithTexture(S2Texture *pTexture,const S2Rect *rt = nullptr);
    //通过文件创建精灵帧
    S2SpriteFrame *CreateWithFile(S2String strFile, const S2Rect *rt = nullptr);
    //通过资源创建精灵帧
    S2SpriteFrame *CreateWithResource(S2uInt unRcid, const S2Rect *rt = nullptr);
    //通过内存创建精灵帧
    S2SpriteFrame *CreateWithMemory(const S2Data pAddr, S2uInt len, const S2Rect *rt = nullptr);

    //释放
    bool Release(S2SpriteFrame *pSpriteFrame);

    //清理所有引用次数为1的对象
    void Purge();
private:
    //取得Md5Key
    S2String GetMd5Key(SValue key);
private:
    S2Map<S2String ,S2SpriteFrame *>     m_mapSpriteFrames;
};
#endif