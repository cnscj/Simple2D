/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2017-08-30 00:00:00 
 * @Brief: 精灵动画类
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-08 11:37:14
 * @Last Modified log: 
 */
#ifndef _S2SPRITEANIMATION_H_
#define _S2SPRITEANIMATION_H_
#include "../s2Core/S2Object.h"
#include "S2SpriteFrame.h"
class S2Sprite;
class S2SpriteAnimation : public S2Object
{
public:
    S2SpriteAnimation();
    ~S2SpriteAnimation();
public:
    //通过数组的方式创建动画
    S2SpriteAnimation *CreateWithSpriteFrames(S2SpriteFrame **sframes, int len, double dDelay = 0.1f);
    S2SpriteAnimation *CreateWithSpriteFrames(S2Array<S2SpriteFrame *> *frames, double dDelay = 0.1f);
    S2SpriteAnimation *CreateWithSpriteFrames(S2List<S2SpriteFrame *> *frames, double dDelay = 0.1f);
    //调用SpriteFrame生成精灵帧
    S2SpriteAnimation *CreateWithTextureSheet(S2Texture *pTexture, int xSrc, int ySrc, int nFrameWidth, int nFrameHeight, int row, int col, double dDelay = 0.1f);
    //通过纹理路径创建
    S2SpriteAnimation *CreateWithTextureFileSheet(S2String strFile, int xSrc, int ySrc, int nFrameWidth, int nFrameHeight, int row, int col, double dDelay = 0.1f);
    //通过图片组加载
    S2SpriteAnimation *CreateWithTextureFilesName(S2String strFileFromat, int nStartCount, int nEndCount, double dDelay = 0.1f);
public:
    //是否循环播放
    void SetIsCycle(bool bCycle);
    bool GetIsCycle() const;

    //是否暂停
    void SetIsPause(bool bPause);
    bool GetIsPause() const;

    //是否逆序
    void SetIsReverse(bool bReverse);
    bool GetIsReverse() const;

    //设置获取帧延迟
    void SetFrameDelay(double dDelay);
    double GetFrameDelay() const;

    //设置获取当前绘制序列
    void SetDrawIndex(int nIndex);
    int GetDrawIndex()const ;

    //获取帧数量
    S2uInt GetFrameCount() const;

public:
    //添加帧
    void AddFrame(S2SpriteFrame *pFrame);

    //移除帧
    void RemoveFrame(S2SpriteFrame *pFrame,bool bRelease=true);
    void RemoveAllFrames(bool bRelease=true);

    //取得某帧
    S2SpriteFrame *GetFrameByIndex(S2uInt index)const;
    S2SpriteFrame *GetCurFrame()const;

    //现在的状态
    int GetState()const;
public:
    //更新-状态更新
    S2Result Update(S2Sprite *pSprite,float fDelay);

    //换帧操作
    S2SpriteFrame *NextFrame(S2Sprite *pSprite);

private:
    /*动画的基本属性*/
    S2Array<S2SpriteFrame *>    m_spriteFrames;    //多个帧组成的画面
    ///
    double                      m_dFrameDelay;     //帧率
    double                      m_dNextTime;       //下一次换帧时间
    double                      m_dTotalTime;      //时间叠加
    ///
    bool                        m_bCycle;          //是否循环播放
    bool                        m_bPause;          //是否暂停播放帧
    bool                        m_bReverse;        //是否逆序播放
    bool                        m_bAutoAdjust;     //是否自动调整
    ///
    int                         m_nDrawIndex;      //记录绘制的位图下标
    int                         m_nState;          //记录状态
};

#endif