/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-27 14:17:37 
 * @Brief: 循环行为类
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-27 15:18:15
 * @Last Modified log: 
 */
#include "S2ForeverAction.h"
const S2Result S2ForeverAction::ACTION_RESULT_ONCE = GetResultUID();

S2ForeverAction::S2ForeverAction(S2Action *pTarget)
:m_pTarget(pTarget), OnOnce([](S2SceneNode *){})
{

}
S2ForeverAction::~S2ForeverAction()
{

}


//逻辑更新
S2Result S2ForeverAction::Update(S2SceneNode *pNode,float fDelay)
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

S2Action *S2ForeverAction::GetTarget()const
{
    return m_pTarget;
}
void S2ForeverAction::Reset()
{
    if (m_pTarget)
        m_pTarget->Reset();
    else
        S2Action::Reset();

}