/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-18 14:06:48 
 * @Brief: 精灵动画
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-27 15:28:06
 * @Last Modified log: 
 */
#include "S2SpriteAnimation.h"
#include "S2SpriteFrame.h"
#include "S2Sprite.h"
S2SpriteAnimation::S2SpriteAnimation()
:m_dFrameDelay(0.1), m_dNextTime(0), m_dTotalTime(0), m_bCycle(true), m_bPause(false), m_bReverse(false), m_nDrawIndex(0), m_nState(0)
{

}
S2SpriteAnimation::~S2SpriteAnimation()
{
    RemoveAllFrames(true);
}

//通过数组的方式创建动画
S2SpriteAnimation *S2SpriteAnimation::CreateWithSpriteFrames(S2SpriteFrame **frames, int len, double dDelay)
{
    if(frames)
    {
        RemoveAllFrames(true);
        for(int i = 0 ;i <len ; ++i)
        {
            AddFrame(frames[i]);
        }
        return this;
    }
    return nullptr;
}
S2SpriteAnimation *S2SpriteAnimation::CreateWithSpriteFrames(S2Array<S2SpriteFrame *> *frames, double dDelay)
{
    if(frames)
    {
        RemoveAllFrames(true);
        m_spriteFrames = *frames;
        return this;
    }
    return nullptr;
}
S2SpriteAnimation *S2SpriteAnimation::CreateWithSpriteFrames(S2List<S2SpriteFrame *> *frames, double dDelay)
{
    if(frames)
    {
        RemoveAllFrames(true);
        for(auto &it = frames->begin(); it != frames->end() ; ++it)
        {
            AddFrame(*it);
        }
        return this;
    }
    return nullptr;
}

//调用SpriteFrame生成精灵帧
S2SpriteAnimation *S2SpriteAnimation::CreateWithTextureSheet(S2Texture *pTexture, int xSrc, int ySrc, int nFrameWidth, int nFrameHeight, int row, int col, double dDelay)
{
    if(pTexture)
    {
        RemoveAllFrames(true);
        S2Rect rt;
        for(int j=0;j<col;++j)
        {
            rt.top = ySrc + j*nFrameHeight;
            rt.bottom = rt.top + nFrameHeight;
            for(int i=0;i<col;++i)
            {
                rt.left = xSrc + i*nFrameWidth;
                rt.right = rt.left + nFrameWidth;
                
                auto pSpriteFrame = S2Object::Create<S2SpriteFrame>();
                if (pSpriteFrame->CreateWithTexture(pTexture, &rt))
                {
                    AddFrame(pSpriteFrame);
                }
            }
        }
        return this;
    }
    return nullptr;
}
//通过纹理路径创建
S2SpriteAnimation *S2SpriteAnimation::CreateWithTextureFileSheet(S2String strFile, int xSrc, int ySrc, int nFrameWidth, int nFrameHeight, int row, int col, double dDelay)
{
    
    RemoveAllFrames(true);

    S2Rect rt;
    for(int j=0;j<col;++j)
    {
        rt.top = ySrc + j*nFrameHeight;
        rt.bottom = rt.top + nFrameHeight;
        for(int i=0;i<col;++i)
        {
            rt.left = xSrc + i*nFrameWidth;
            rt.right = rt.left + nFrameWidth;
            auto pSpriteFrame = S2Object::Create<S2SpriteFrame>();
            if (pSpriteFrame->CreateWithFile(strFile, &rt))
            {
                AddFrame(pSpriteFrame);
            }
        }
    }
    return this;

}
//通过图片组加载
S2SpriteAnimation *S2SpriteAnimation::CreateWithTextureFilesName(S2String strFileFromat, int nStartCount, int nEndCount, double dDelay)
{
    RemoveAllFrames(true);

    char file[512];
    const char *fileFormat = strFileFromat.c_str();

    for (int i = nStartCount ; i <= nEndCount ; ++i)
    {
        #if defined __GNUC__ || defined __APPLE__
        sprintf(file,fileFormat,i);
        #else
        sprintf_s(file, fileFormat, i);
        #endif
        //从文件中创建精灵帧
        auto pSpriteFrame = S2Object::Create<S2SpriteFrame>();
        if (pSpriteFrame->CreateWithFile(file))
        {
            AddFrame(pSpriteFrame);
        }

    }
    m_dFrameDelay = dDelay;
    return this;
}

//是否循环播放
void S2SpriteAnimation::SetIsCycle(bool bCycle)
{
    m_bCycle = bCycle;
}
bool S2SpriteAnimation::GetIsCycle() const
{
    return m_bCycle;
}

//是否暂停
void S2SpriteAnimation::SetIsPause(bool bPause)
{
    m_bPause = bPause;
}
bool S2SpriteAnimation::GetIsPause()const
{
    return m_bPause;
}

//是否逆序
void S2SpriteAnimation::SetIsReverse(bool bReverse)
{
    m_bReverse = bReverse;
}
bool S2SpriteAnimation::GetIsReverse()const
{
    return m_bReverse;
}

//设置获取帧延迟
void S2SpriteAnimation::SetFrameDelay(double dDelay)
{
    m_dFrameDelay = dDelay;
}
double S2SpriteAnimation::GetFrameDelay()const
{  
    return m_dFrameDelay;
}

//设置获取当前绘制序列
void S2SpriteAnimation::SetDrawIndex(int nIndex)
{
    m_nDrawIndex = nIndex;
}
int S2SpriteAnimation::GetDrawIndex()const
{
    return m_nDrawIndex;
}

//获取帧数量
S2uInt S2SpriteAnimation::GetFrameCount()const
{
    return m_spriteFrames.size();
}

//添加帧
void S2SpriteAnimation::AddFrame(S2SpriteFrame *pFrame)
{
    pFrame->Retain();
    m_spriteFrames.push_back(pFrame);
}

//移除帧
void S2SpriteAnimation::RemoveFrame(S2SpriteFrame *pFrame,bool bRelease)
{
    for (auto &it =m_spriteFrames.begin() ; it != m_spriteFrames.end();)
    {
        if(*it == pFrame)
        {
            if(bRelease)
                (*it)->Release();
            m_spriteFrames.erase(it++);
        }else ++it;

    }
}
void S2SpriteAnimation::RemoveAllFrames(bool bRelease)
{
    for (auto &it = m_spriteFrames.begin() ; it != m_spriteFrames.end();++it)
    {
        if(bRelease)
            (*it)->Release();
    }
    m_spriteFrames.clear();
}

//取得某帧
S2SpriteFrame *S2SpriteAnimation::GetFrameByIndex(S2uInt index)const
{
    if(index >= m_spriteFrames.size())
        return nullptr;
    return m_spriteFrames.at(index);
}
S2SpriteFrame *S2SpriteAnimation::GetCurFrame()const
{
    return m_spriteFrames.at(m_nDrawIndex);
}

int S2SpriteAnimation::GetState()const
{
    return m_nState;
}

//更新-状态更新
S2Result S2SpriteAnimation::Update(S2Sprite *pSprite,float fDelay)
{
    //数组不为空
    S2Result res = 0;
    if (!m_spriteFrames.empty())
    {
        m_dTotalTime += fDelay;
        if (m_dTotalTime >= m_dNextTime)
        {
            //换帧操作
            NextFrame(pSprite);

            //下次换帧时间
            m_dNextTime = m_dTotalTime + m_dFrameDelay;
   
        }
        else m_nState = 0;
        res = GetState();
    }
    return res;
}

//换帧操作
S2SpriteFrame *S2SpriteAnimation::NextFrame(S2Sprite *pSprite)
{
    if (!m_spriteFrames.empty())
    {
        auto frame = GetFrameByIndex(m_nDrawIndex);        //取得当前帧;
        //暂停表示停在这帧上
        m_nState = 1;
        if (!m_bPause)
        {
            //正向播放
            if (!m_bReverse)
            {
                ++m_nDrawIndex;                        //列序号递增
                //当列序号超过列总数时归0，重新循环    
                if (m_nDrawIndex >= (int)GetFrameCount())
                {
                    //允许循环则归0
                    if (m_bCycle){
                        m_nDrawIndex = 0;
                        m_nState = 2;
                    }
                    else
                    {
                        m_nDrawIndex = GetFrameCount() - 1;
                        m_bPause = true;            //暂停播放
                        m_nState = 3;
                    }
                }
            }
            else
            {
                --m_nDrawIndex;                        //列序号递减
                //当列序号小于列总数时归位，重新循环    
                if (m_nDrawIndex < 0)
                {
                    //允许循环则归0
                    if (m_bCycle){
                        m_nDrawIndex = GetFrameCount() - 1;
                        m_nState = 2;
                    }
                    else
                    {
                        m_nDrawIndex = 0;           //暂停在最后一张
                        m_bPause = true;            //暂停播放
                        m_nState = 3;
                    }
                }
            }
        }
        if (pSprite){
            pSprite->SetSpriteFrame(frame);
        }
        return frame;
    }else return nullptr;
}