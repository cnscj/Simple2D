/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-27 15:35:40 
 * @Brief: 重复行为实现类
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-27 15:42:05
 * @Last Modified log: 
 */
#include "S2ActionRepeat.h"

S2ActionRepeat::S2ActionRepeat(S2Action *pTarget,int nTimes)
:S2FiniteTimeAction(pTarget),m_nTimes(nTimes)
{

}
S2ActionRepeat::~S2ActionRepeat()
{

}

void S2ActionRepeat::SetTimes(int nTimes)
{
    m_nTimes = nTimes;
}
int S2ActionRepeat::GetTimes() const
{
    return m_nTimes;
}

S2Result S2ActionRepeat::Update(S2SceneNode *pNode,float fDelay)
{
    if (m_nTimes != 0)
    {    
        S2Result res = S2FiniteTimeAction::Update(pNode,fDelay);
        if(res == ACTION_RESULT_FINISH)
        {
            --m_nTimes; 
            if (m_nTimes == 0)
            {
                return ACTION_RESULT_FINISH;
            }
            else
            {
                Reset();
                return ACTION_RESULT_ONCE;
            }
        }
        return res;
    }
    else return ACTION_RESULT_FINISH;
}