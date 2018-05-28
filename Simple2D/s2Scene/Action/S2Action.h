/**
*    S2Action
*    @brief 结点行为类
*    @author cnscj
*    @link -
*    @version v1.0
*    @date 07/03/2018
*    @update 07/03/2018
*/

#ifndef _S2ACTION_H_
#define _S2ACTION_H_
#include "../../s2Core/S2Object.h"
class S2SceneNode;
class S2Action :public S2Object
{
    friend class S2ActionManager;
protected:
    static S2Result sm_nResultUids;
    static S2Result GetResultUID();
public:
    const static S2Result ACTION_RESULT_ERROR;        //执行出错
    const static S2Result ACTION_RESULT_NORMAL;       //正常返回
    const static S2Result ACTION_RESULT_FINISH;       //执行结束
public:
    //逻辑更新
    virtual S2Result Update(S2SceneNode *pNode,float fDelay);
    //是否已经完成
    virtual bool IsFinish() const;
    //是否暂停
    virtual bool IsPause() const;
    virtual void Pause();
    virtual void Resume();
    //复位
    virtual void Reset();
    //动作结束回调
    S2Function<void(S2SceneNode *)> OnFinish;
protected:
    //行为更新的回调
    virtual S2Result OnUpdate(S2SceneNode *pNode,float fDelay);

    //重置
    virtual void OnReset();
protected:
    S2Action();
    virtual ~S2Action();

private:
    bool m_bIsFinish;       //动作是否完成
    bool m_bIsPause;        //是否暂停
};
#endif