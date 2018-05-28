/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-03-07 16:12:42
 * @Brief: 场景结点接口 
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-26 13:03:29
 * @Last Modified log: 
 */

#ifndef _S2DIRECTOR_H_
#define _S2DIRECTOR_H_

#include "../s2Base/sDispatch/SDispatcher.h"
#include "../s2Base/sSchedule/SScheduler.h"
#include "../s2Core/S2Singleton.hpp"
#include "../s2Engine/S2SteadyFramePulser.h"
#include "../s2Render/S2View.h"

class S2Camera;
class S2Scene;

class S2Director : public S2Singleton<S2Director>
{
public:
    S2Director();
    virtual ~S2Director();
public:
    //取得正在运行的场景
    const S2Scene *GetRunningScene() const;

    //进入AppDelegate主循环运行的场景，仅在运行第一个场景时调用
    void RunWithScene(S2Scene *pScene);

    //暂停当前场景，push到场景堆栈，运行新场景
    void PushScene(S2Scene *pScene);

    //从场景堆栈中pop场景，删除当前场景（不入栈）
    void PopScene();

    //从场景堆栈中pop出所有场景，栈底场景替换当前场景，删除当前场景（不入栈）
    void PopToRootScene();

    //场景替换，删除当前场景（不入栈）
    void ReplaceScene(S2Scene *pScene);

    //暂停当前场景
    void PauseScene(S2Scene *pScene);
    //恢复被暂停的当前场景
    void ResumeScene(S2Scene *pScene);

public:
    //取得全局定时器
    SScheduler *GetScheduler() const;
    //取得事件分发器
    SDispatcher *GetDispatcher() const;

    //设置\获取摄像机
    void SetCamera(const S2Camera *pCamera);
    S2Camera *GetCamera() const;

    //设置\获取渲染器实例
    void SetRenderView(const S2View *pView);
    S2View *GetRenderView() const;

public:
    //设置\获取帧延迟
    void SetFramesPerSecond(double dFrames);
    double GetFramesPerSecond() const;

    //设置锚点
    void SetAnchorPoint(const S2Vector2 &pt);
    const S2Vector2 &GetAnchorPoint() const;

public:
    //主循环
    void MainLoop();

    //数据更新
    void Update(float fDelay);

    //暂停当前场景
    void Pause();
    //恢复被暂停的当前场景
    void Resume();
    //终止执行，释放运行中的场景
    void End();

private:
    /* 各部分组件 */
    S2SteadyFramePulser            m_pluser;                             //脉冲
    SScheduler                     m_scheduler;                          //定时调度器
    SDispatcher                    m_dispatcher;                         //事件分发器

    S2Camera                       *m_pCamera;                           //摄像机
    S2View                         *m_pView;                             //渲染视图

    /////////
    S2Scene                        *m_pCurrentScene;                     //当前正在运行的场景
    S2Stack<S2Scene *>             m_stackScenes;                        //储存场景的栈
    S2Vector2                      m_anchorPoint;                        //锚点

};
#endif