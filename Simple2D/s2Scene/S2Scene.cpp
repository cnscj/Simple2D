/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-09 16:39:31 
 * @Brief: 
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-09 16:41:04
 * @Last Modified log: 
 */
#include "S2Scene.h"
S2Scene::S2Scene()
:m_bIsPause(false)
{

}
S2Scene::~S2Scene()
{

}

//进入场景
void S2Scene::OnEnter()
{

}
//进入场景的特效
void S2Scene::OnEnterTransitionDidFinish()
{

}
//退出场景
void S2Scene::OnExit()
{

}
//退出场景的特效
void S2Scene::OnExitTransitionDidStart()
{

}

/////
//场景暂停调用
void S2Scene::OnPause()
{

}
//场景恢复调用
void S2Scene::OnResume()
{
    
}

//////
void S2Scene::Enter()
{
    OnEnter();
}

void S2Scene::Exit()
{
    OnExit();
}

void S2Scene::Pause()
{
    m_bIsPause = true;
    OnPause();
}

void S2Scene::Resume()
{
    m_bIsPause = false;
    OnResume();
}