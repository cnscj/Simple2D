#include "S2RenderSystem.h"
#include "S2View.h"
S2RenderSystem::S2RenderSystem()
{

}
S2RenderSystem::~S2RenderSystem()
{

}
//初始化视图
S2View *S2RenderSystem::CreateViewWithHandle(void *hWnd)
{
    auto pView = S2Object::Create<S2View>();
    if (pView->CreateWithHandle(hWnd))
        return pView;
    return nullptr;
}
//创建View
S2View *S2RenderSystem::CreateViewWithSize(S2String strName, int nWidth, int nHeight)
{
    auto pView = S2Object::Create<S2View>();
    if (pView->CreateWithSize(strName, nWidth, nHeight))
        return pView;
    return nullptr;
}