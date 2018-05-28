/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-03-07 00:00:00 
 * @Brief: 精灵类
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-07 16:54:15
 * @Last Modified log: 
 */

#ifndef _S2SPRITE_H_
#define _S2SPRITE_H_

#include "S2SceneNode.h"

class S2SpriteFrame;
class S2SpriteAnimation;
class S2Animation;
class S2Animate;
class S2Texture;

class S2Sprite :public S2SceneNode
{
public:
    static const S2uInt MATRIX_CHANGED = 1;      //矩阵变换
public:
    S2Sprite();
    virtual ~S2Sprite();
public:
    //通过精灵帧创建精灵-尺寸使用精灵帧的尺寸
    S2Sprite *CreateWithSpriteFrame(S2SpriteFrame *pSpriteFrame);
    //通过纹理创建精灵
    S2Sprite *CreateWithTexture(S2Texture *pTexture, const S2Rect *rt = nullptr);
    //从文件中加载
    S2Sprite *CreateWithFile(const S2String &strPath, const S2Rect *rt = nullptr);
    //从资源中加载
    S2Sprite *CreateWithResource(S2uInt uRcid,const S2Rect *rt = nullptr);
    //从内存中创建
    S2Sprite *CreateWithMemory(const S2Data in, S2uInt length, const S2Rect *rt = nullptr);
    //从动画中创建
    S2Sprite *CreateWithAnimation(S2SpriteAnimation *pAnimation);
    //从动画的某帧创建
    S2Sprite *CreateWithAnimationIndex(const S2SpriteAnimation *pAnimation, S2uInt index);
public:
    //更换新的精灵帧
    void SetSpriteFrame(S2SpriteFrame *pFrame);
    const S2SpriteFrame *GetSpriteFrame() const;

    //设置色键
    void SetColorKey(S2ColorRef dwColorKey);
    const S2ColorRef &GetColorKey();

    //设置不透明度
    void SetOpacity(float nOpacity);
    float GetOpacity() const;


    //设置旋转
    void SetRotation(float fRadian);//弧度制
    void SetRotation3D(float x, float y, float z);
    
    //水平竖直翻转
    void SetFlipX(bool bFlip);
    void SetFlipY(bool bFlip);

    //关于XY轴倾斜
    void SetSkewX(float fSkewX);
    void SetSkewY(float fSkewY);

    //设置缩放比率
    void SetScale(float fScale);
    void SetScaleX(float fScaleX);
    void SetScaleY(float fScaleY);

public:
    //播放动画
    //当成一种永远重复的动作来处理
    S2Animate *PlayAnimation(S2SpriteAnimation *pAnimation);
    void StopAnimation();

    //自适应纹理大小
    void AdaptiveSize();
public:
    //重载逻辑更新函数
    virtual void OnUpdate(float fDelay);
    //绘制结点
    virtual void OnDraw(S2Renderer *pRenderer, const S2Matrix *mat4, S2uInt flag);
protected:
    S2SpriteFrame     *m_pMainFrame;              //主显精灵帧
    S2Action          *m_pAnimate;                //精灵动画

    S2Float           m_fOpacity;                 //不透明度
    S2ColorRef        m_dwColorKey;               //透明色键

    float             m_fRadian;                  //旋转弧度
    S2Vector3         m_vec3Rotation3D;           //旋转向量
    float             m_fSkewX, m_fSkewY;         //倾斜角度
    float             m_fScaleX, m_fScaleY;       //宽高缩放比
    bool              m_bFlipX, m_bFlipY;         //水平竖直翻转

};
#endif