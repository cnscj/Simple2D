/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-27 14:27:23 
 * @Brief: 行为序列帧
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-27 15:17:31
 * @Last Modified log: 
 */

#include "S2SequenceAction.h"
S2SequenceAction::S2SequenceAction()
:S2FiniteTimeAction(nullptr), m_nCurIndex(0)
{

}
S2SequenceAction::~S2SequenceAction()
{
    RemoveAllActions();
}

//添加行为
void S2SequenceAction::AddAction(S2Action *pAction)
{
    pAction->Retain();
    m_ationsArray.push_back(pAction);
}

//移除行为
void S2SequenceAction::RemoveAction(S2Action *pAction,bool bRelease)
{
    for (auto &it = m_ationsArray.begin();it != m_ationsArray.end();)
    {
        if(*it == pAction)
        {
            if(bRelease)(*it)->Release();
            m_ationsArray.erase(it++);
        }else ++it;

    }
}

void S2SequenceAction::RemoveAllActions(bool bRelease)
{
    for (auto &it = m_ationsArray.begin();it != m_ationsArray.end();)
    {
        if(bRelease) (*it)->Release();
        m_ationsArray.erase(it++);
    }
}

//取得\设置当前执行的活动下标
void S2SequenceAction::SetCurIndex(int nIndex)
{
    m_nCurIndex = nIndex;
}
int S2SequenceAction::GetCurIndex()const
{
    return m_nCurIndex;
}

//取得行为数量
S2uInt S2SequenceAction::GetActionCount()
{
    return m_ationsArray.size();
}

//逻辑更新
S2Result S2SequenceAction::Update(S2SceneNode *pNode,float fDelay)
{
    if(!m_ationsArray.empty())
    {
        S2Result res = m_ationsArray.at(m_nCurIndex)->Update(pNode,fDelay);
        if(res == ACTION_RESULT_FINISH)
        {
            ++m_nCurIndex;
            if(m_nCurIndex >= (int)m_ationsArray.size())
            {
                return ACTION_RESULT_FINISH;
            }
            return ACTION_RESULT_ONCE;
        }
    }
    return ACTION_RESULT_NORMAL;
}

void S2SequenceAction::OnReset()
{
    for (auto &it : m_ationsArray)
    {
        it->Reset();
    }
    m_nCurIndex = 0;
}