/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-22 13:05:33 
 * @Brief: 导演类实现
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-07 19:35:33
 * @Last Modified log: 
 */
#include "S2Director.h"
#include "S2Scene.h"

#include "S2Camera.h"
S2Director::S2Director()
:m_pluser(0.016f)
,m_pView(nullptr), m_pCamera(nullptr), m_pCurrentScene(nullptr)
,m_anchorPoint(0,0)//场景结点已左上角为坐标原点
{
    SetCamera(S2Object::Create<S2Camera>());
}
S2Director::~S2Director()
{
    S2SAFERELEASE(m_pCamera);
    S2SAFERELEASE(m_pView);
}

//取得正在运行的场景
const S2Scene *S2Director::GetRunningScene() const
{
    return m_pCurrentScene;
}

//进入AppDelegate主循环运行的场景，仅在运行第一个场景时调用
void S2Director::RunWithScene(S2Scene *pScene)
{
    m_pCurrentScene = (S2Scene *)pScene;
    m_pCurrentScene->Enter();
}

//暂停当前场景，push到场景堆栈，运行新场景
void S2Director::PushScene(S2Scene *pScene)
{
    PauseScene(m_pCurrentScene);
	m_stackScenes.push(m_pCurrentScene);
	m_pCurrentScene->Exit();

    m_pCurrentScene = (S2Scene *)pScene;
	m_pCurrentScene->Enter();
}

//从场景堆栈中pop场景，删除当前场景（不入栈）
void S2Director::PopScene()
{
	m_pCurrentScene->Exit();
    S2SAFERELEASE(m_pCurrentScene);

	m_pCurrentScene = m_stackScenes.top();
    m_stackScenes.pop();
    ResumeScene(m_pCurrentScene);
}

//从场景堆栈中pop出所有场景，栈底场景替换当前场景，删除当前场景（不入栈）
void S2Director::PopToRootScene()
{
    auto pBottom = (S2Scene *)nullptr;
	do
	{
        S2SAFERELEASE(pBottom);
        pBottom = m_stackScenes.top();
        m_stackScenes.pop();
	
    } while (!m_stackScenes.empty());
    if(pBottom) ReplaceScene(pBottom);
}

//场景替换，删除当前场景（不入栈）
void S2Director::ReplaceScene(S2Scene *pScene)
{
    m_pCurrentScene->Exit();
    S2SAFERELEASE(m_pCurrentScene);

    m_pCurrentScene = (S2Scene *)pScene;
	m_pCurrentScene->Enter();
}

//暂停当前场景
void S2Director::PauseScene(S2Scene *pScene)
{
    pScene->Pause();
}
//恢复被暂停的当前场景
void S2Director::ResumeScene(S2Scene *pScene)
{
    pScene->Resume();

}

//取得全局定时器
SScheduler *S2Director::GetScheduler() const
{
    auto pScheduler = (SScheduler *)&m_scheduler;
    return pScheduler;
}
//取得事件分发器
SDispatcher *S2Director::GetDispatcher() const
{
    auto pDispatcher = (SDispatcher *)&m_dispatcher;
    return pDispatcher;
}

//设置\获取摄像机
void S2Director::SetCamera(const S2Camera *pCamera)
{
    S2SAFERELEASE(m_pCamera);
    m_pCamera = (S2Camera *)pCamera;
    if (m_pCamera)m_pCamera->Retain();
}
S2Camera *S2Director::GetCamera() const
{
    return m_pCamera;
}

void S2Director::SetRenderView(const S2View *pView)
{
    S2SAFERELEASE(m_pView);
    m_pView = (S2View *)pView;
    m_pView->Retain();
}
S2View *S2Director::GetRenderView() const
{
    return m_pView;
}

//设置\获取帧延迟
void S2Director::SetFramesPerSecond(double dFrames)
{
    m_pluser.SetFrameDelay(1.0f / dFrames);
}

double S2Director::GetFramesPerSecond() const
{
    return 1.0f/m_pluser.GetCurFrameDelay();
}

//设置锚点
void S2Director::SetAnchorPoint(const S2Vector2 &pt)
{
    m_anchorPoint = pt;
}
const S2Vector2 &S2Director::GetAnchorPoint() const
{
    return m_anchorPoint;
}

//主循环
void S2Director::MainLoop()
{
    //取得时间流逝
    if (m_pluser.Poll())
    {
        m_dispatcher.DealAllEvents();                       //事件处理
        m_scheduler.DealAllTasks();                         //任务处理

        //数据更新
        double dElpased = m_pluser.GetCurFrameDelay();
        Update((float)dElpased);
    }
}


void S2Director::Update(float fDelay)
{
    //开始渲染
    auto pRenderer = m_pView->GetViewRenderer();

    //摄像机更新
    if (m_pCamera)m_pCamera->Update(pRenderer);

    //渲染过程
    pRenderer->BeginRender();

    if (m_pCurrentScene)m_pCurrentScene->DoVisit();
    //XXX:打印帧率

    //结束渲染
    pRenderer->EndRender();

}


//暂停当前场景
void S2Director::Pause()
{
    return PauseScene(m_pCurrentScene);
}
//恢复被暂停的当前场景
void S2Director::Resume()
{
    return ResumeScene(m_pCurrentScene);
}
//终止执行，释放运行中的场景
void S2Director::End()
{
    //结束游戏释放
}