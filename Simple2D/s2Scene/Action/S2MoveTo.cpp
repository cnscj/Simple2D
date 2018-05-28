/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-27 11:42:22 
 * @Brief: MoveTo动作
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-27 16:01:35
 * @Last Modified log: 
 */
#include "S2MoveTo.h"
#include "../S2SceneNode.h"
S2MoveTo::S2MoveTo()
:S2ActionInterval(nullptr, 0), m_fTime(0.f), m_fSpeed(10.0f), m_lastStep(0.f,0.f)
{

}
S2MoveTo::S2MoveTo(float fTime, const S2Point &p, float fSpeed)
: S2ActionInterval(this, 0), m_fSpeed(1.0f)
{
    SetTime(fTime);
}
S2MoveTo::S2MoveTo(const S2Point &p, float fSpeed)
: S2ActionInterval(this, 0), m_destPoint(p), m_fSpeed(fSpeed), m_fTime(0)
{
 
}
S2MoveTo::~S2MoveTo()
{

}

//设置\获取目标点
void S2MoveTo::SetDestPoint(const S2Point &p)
{
    m_destPoint = p;
}
const S2Point &S2MoveTo::GetDestPoint() const
{
    return m_destPoint;
}

float S2MoveTo::GetSpeed()const
{
    return m_fSpeed;
}
void S2MoveTo::SetSpeed(float nSpeed)
{
    m_fSpeed = nSpeed;
}

float S2MoveTo::GetTime()
{
    return (float)::fabs(m_fTime);
}
void S2MoveTo::SetTime(double fTime)
{
    m_fTime = -(float)::fabs(fTime);
}

S2Result S2MoveTo::OnUpdate(S2SceneNode *pNode,float fDelay)
{
    //计算起点和终点两点间的水平和垂直距离
    float sx = (float)(m_destPoint.x - pNode->GetPosition().x);
    float sy = (float)(m_destPoint.y - pNode->GetPosition().y);
    float dist = hypot(sx, sy);
    float fStepX, fStepY;
    //根据距离算法每步应走的大小
    //如果时间初始化,则用时间进行
    if (m_fTime < 0)
    {
        m_fTime = -m_fTime;
        m_fSpeed = dist / m_fTime;
    }
    if (dist)
    {
        fStepX = m_fSpeed * sx / dist;//向量规范化
        fStepY = m_fSpeed * sy / dist;//向量规范化

        //判断物体离目标的直线距离是否大于一次移动的步长，如果小于步长，则直接设置物体到有效目标点
        //目的是防止始终到不了终点这种情况
        if (dist <= hypot(fStepX, fStepY))
        {
            pNode->SetPosition(m_destPoint);		//直接设置对象到目标点
            m_fTime = 0.f;
            return ACTION_RESULT_FINISH;
        }
        else
        {
            /*如果未到终点*/
            const S2Point &pt = pNode->GetPosition();
            m_lastStep.x += fStepX; m_lastStep.y += fStepY;
            const S2Point &step = S2Point((int)m_lastStep.x, (int)m_lastStep.y);
            S2Point next = step + pt;
            pNode->SetPosition(next);
            m_lastStep.x = m_lastStep.x - step.x; m_lastStep.y = m_lastStep.y - step.y;

            //重新计算所需时间
            m_fTime = (float)::fabs((hypot(m_destPoint.x - next.x, m_destPoint.y - next.y)) / m_fSpeed);

        }
    }
    else
    {
        pNode->SetPosition(m_destPoint);		//直接设置对象到目标点
        m_fTime = 0.f;
        return ACTION_RESULT_FINISH;
    }

    return ACTION_RESULT_FRAME;
}

void S2MoveTo::OnReset()
{
    m_fTime = 0.f;
    m_fSpeed = 10.0f; 
    m_lastStep.x = 0.f; m_lastStep.y = 0.f;

}