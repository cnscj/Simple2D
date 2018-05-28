/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-20 08:52:49 
 * @Brief: 行为序列
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-27 14:34:32
 * @Last Modified log: 
 */
#ifndef _S2SEQUENCEACTION_H_
#define _S2SEQUENCEACTION_H_
#include "S2FiniteTimeAction.h"
class S2SequenceAction : public S2FiniteTimeAction
{
public:
    S2SequenceAction();
    virtual ~S2SequenceAction();
public:
    //添加行为
    void AddAction(S2Action *pAction);

    //移除行为
    void RemoveAction(S2Action *pAction,bool bRelease = true);

    //移除所有行为
    void RemoveAllActions(bool bRelease = true);
public:
    //取得\设置当前执行的活动下标
    void SetCurIndex(int nIndex);
    int GetCurIndex() const;

    //取得行为数量
    S2uInt GetActionCount();
public:
    //逻辑更新
    virtual S2Result Update(S2SceneNode *pNode,float fDelay);
protected:
    virtual void OnReset();
private:
    S2Array<S2Action *>     m_ationsArray;
    int                     m_nCurIndex;
};
#endif