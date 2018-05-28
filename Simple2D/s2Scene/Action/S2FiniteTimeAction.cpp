/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-27 13:22:25 
 * @Brief: 有限次行为定义
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-27 15:17:57
 * @Last Modified log: 
 */
#include "S2FiniteTimeAction.h"

const S2Result S2FiniteTimeAction::ACTION_RESULT_ONCE = GetResultUID();

S2FiniteTimeAction::S2FiniteTimeAction(S2Action	*pTarget)
:m_pTarget(pTarget), OnOnce([](S2SceneNode *){})
{

}
S2FiniteTimeAction::~S2FiniteTimeAction()
{

}


//逻辑更新
S2Result S2FiniteTimeAction::Update(S2SceneNode *pNode,float fDelay)
{
    S2Result res = ACTION_RESULT_NORMAL;
    if (m_pTarget)
        res = m_pTarget->Update(pNode,fDelay);
    else
        res = S2Action::Update(pNode,fDelay);
    if(res == ACTION_RESULT_ONCE)
    {
        OnOnce(pNode);
    }
    
    return res;
}
S2Action *S2FiniteTimeAction::GetTarget()const
{
    return m_pTarget;
}

void S2FiniteTimeAction::Reset()
{
    if (m_pTarget)
        m_pTarget->Reset();
    else
        S2Action::Reset();
}