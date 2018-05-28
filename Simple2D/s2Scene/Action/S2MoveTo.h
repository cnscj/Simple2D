/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-22 00:29:11 
 * @Brief: 结点移动类
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-27 11:44:09
 * @Last Modified log: 
 */

#ifndef _S2MOVETO_H_
#define _S2MOVETO_H_
#include "S2ActionInterval.h"
class S2SpriteAnimation;
class S2MoveTo : public S2ActionInterval
{
public:
    //TODO:这种创建方式不严谨,无法得知是否创建成功
    S2MoveTo();
    S2MoveTo(float fTime, const S2Point &p, float fSpeed = 1.0f);
    S2MoveTo(const S2Point &p, float fSpeed = 1.0f);
    ~S2MoveTo();
public:
    //设置\获取目标点
    void SetDestPoint(const S2Point &p);
    const S2Point &GetDestPoint() const;

    //设置取得速度
    float GetSpeed()const;
    void SetSpeed(float nSpeed);

    float GetTime();
    void SetTime(double fTime);
public:
    //逻辑更新
    virtual S2Result OnUpdate(S2SceneNode *pNode,float fDelay);

    //重置
    virtual void OnReset();
private:
    S2Point     m_destPoint;            //设置目标点
    S2Vector2   m_lastStep;             //记录步数增量
    float       m_fSpeed;               //所需速度

    float       m_fTime;                //所需时间
};

#endif