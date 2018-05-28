/**
*
*    S2SpriteFrame
*    @brief 精灵帧类-精灵类的最小单位
*    @author ZEROX
*    @link
*    @version v1.0
*    @date 2017-08-30
*    @update 2017-08-30
*/

#ifndef _S2SPRITEFRAME_H_
#define _S2SPRITEFRAME_H_
#include "../s2Core/S2Object.h"
class S2Sprite;
class S2Texture;

class S2SpriteFrame :public S2Object
{
public:
    S2SpriteFrame();
    S2SpriteFrame(S2Texture *pTexture,const S2Rect *rt = nullptr);
    S2SpriteFrame(S2String strPath, const S2Rect *rt = nullptr);
    S2SpriteFrame(S2uInt uRcid, const S2Rect *rt = nullptr);
    S2SpriteFrame(const S2Data data, const S2uInt length, const S2Rect *rt = nullptr);
    ~S2SpriteFrame();
public:
    //通过纹理创建精灵帧
    S2SpriteFrame *CreateWithTexture(S2Texture *pTexture, const S2Rect *rt = nullptr);//裁剪区
    //从文件中加载
    S2SpriteFrame *CreateWithFile(S2String strPath, const S2Rect *rt = nullptr);
    //从资源中加载
    S2SpriteFrame *CreateWithResource(S2uInt uRcid, const S2Rect *rt = nullptr);
    //从内存中创建
    S2SpriteFrame *CreateWithMemory(const S2Data data, const S2uInt length, const S2Rect *rt = nullptr);

public:
    //设置获取纹理
    void SetTexture(S2Texture *pTexture);
    const S2Texture *GetTexture() const;

    //设置裁剪区
    void SetFrameRect(const S2Rect *rt);
    const S2Rect &GetFrameRect() const;

    //获取设置帧宽高
    void SetFrameWidth(int nWidth);
    int GetFrameWidth() const;
    void SetFrameHeight(int nHeight);
    int GetFrameHeight() const;
private:
    //释放占用的纹理
    void __ReleaseTexture();
private:
    S2Texture                *m_pTexture;                //所引用的纹理
    S2Rect                    m_frameRect;               //裁剪区
};

#endif