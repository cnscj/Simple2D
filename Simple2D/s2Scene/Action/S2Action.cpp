/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-27 11:58:01 
 * @Brief: 行为定义
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-27 15:21:59
 * @Last Modified log: 
 */
#include "S2Action.h"
#include "../S2SceneNode.h"
S2Result S2Action::sm_nResultUids = 1;

const S2Result S2Action::ACTION_RESULT_ERROR = -1;                     //执行出错
const S2Result S2Action::ACTION_RESULT_NORMAL = 0;                     //执行正常
const S2Result S2Action::ACTION_RESULT_FINISH = 1;                     //执行结束

S2Result S2Action::GetResultUID()
{
    sm_nResultUids *= 2;
    return sm_nResultUids;
}
//逻辑更新
S2Result S2Action::Update(S2SceneNode *pNode,float fDelay)
{
    if (!m_bIsFinish) 
    {
        if (!m_bIsPause)
        {
            S2Result res = OnUpdate(pNode, fDelay);
            switch (res)
            {
            case ACTION_RESULT_ERROR:
            {
                //错误处理
            }break;
            case ACTION_RESULT_NORMAL:
            {
                //意味着还有下一次
            }break;
            case ACTION_RESULT_FINISH:
            {
                m_bIsFinish = true;
                OnFinish(pNode);
            }break;
            }
            return res;
        }
    }
    return ACTION_RESULT_FINISH;
}
S2Result S2Action::OnUpdate(S2SceneNode *pNode,float fDelay)
{
    return ACTION_RESULT_FINISH;
}

//是否已经完成
bool S2Action::IsFinish() const
{
    return m_bIsFinish;
}

bool S2Action::IsPause()const
{
    return m_bIsPause;
}
void S2Action::Pause()
{
    m_bIsPause = true;
}
void S2Action::Resume()
{
    m_bIsPause = false;
}
//复位
void S2Action::Reset()
{
    m_bIsFinish = false;
    m_bIsPause = false;
    OnReset();
}
void S2Action::OnReset()
{

}
S2Action::S2Action()
: m_bIsFinish(false), m_bIsPause(false), OnFinish([=](S2SceneNode *pNode){pNode->StopAction(this); })
{

}
S2Action::~S2Action()
{

}