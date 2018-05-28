/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-15 11:12:52 
 * @Brief: 场景结点实现
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-15 11:13:20
 * @Last Modified log: 
 */
#include "S2SceneNode.h"
#include "S2Director.h"
#include "../s2Render/S2Renderer.h"
#include "Action/S2Action.h"
#include "../s2Base/sMath/SMathX.hpp"

S2SceneNode::S2SceneNode()
:m_plistChildren(nullptr), m_plistActions(nullptr) 
, m_parent(nullptr), m_nZorder(10000)
, m_nodePosition(0, 0), m_nodeSize(0,0), m_anchorPoint(0.f, 0.f)
,m_bEnabled(true), m_bVisible(true), m_pUserData(nullptr)
{
    SMatrixIdentity(&m_worldMatrix);
}
S2SceneNode::~S2SceneNode()
{
    StopAllActions();  
    RemoveAllChildren();
    S2SAFEDELETE(m_plistActions);
    S2SAFEDELETE(m_plistChildren); 
}
//////////////////////
//添加子节点
void S2SceneNode::AddChild(S2SceneNode *pNode)
{
    AddChild(pNode, m_nZorder);
}
void S2SceneNode::AddChild(S2SceneNode *pNode, int nZorder)
{
    if (pNode)
    {
        if (!pNode->GetParent())
        {
            pNode->m_parent = this;
        }
        else{
            pNode->RemoveFromParent();
        }
        pNode->m_nZorder = nZorder;
        pNode->Retain();
        __InsertNode(pNode, nZorder);
    }
}
//移除结点
void S2SceneNode::RemoveChild(S2SceneNode *pNode, bool bRelease)
{
    if (!m_plistChildren)
        return;

    if (pNode)
    {
        for (auto it = m_plistChildren->begin(); it != m_plistChildren->end();)
        {
            if (*it == pNode)
            {
                (*it)->m_parent = nullptr;
                if (bRelease) (*it)->Release();
                m_plistChildren->erase(it++);
                break;
            }
            else ++it;
        }
    }
}
//从父节点移除
void S2SceneNode::RemoveFromParent(bool bRelease)
{
    if (GetParent())
    {
        GetParent()->RemoveChild(this, bRelease);
    }
}
void S2SceneNode::RemoveAllChildren(bool bRelease)
{
    if (!m_plistChildren)
        return;

    for (auto it = m_plistChildren->begin(); it != m_plistChildren->end(); )
    {
        if (bRelease) (*it)->Release();
        m_plistChildren->erase(it++);
    }
}
/////
//执行行为
void S2SceneNode::RunAction(S2Action *pAction)
{
    if(pAction)
    {
        pAction->Retain();
        __GetActionsList()->push_back(pAction);
    }
}

//移除行为
void S2SceneNode::StopAction(S2Action *pAction, bool bRelease)
{
    if (!m_plistActions)
        return;

    if (pAction)
    {
        for (auto &it = m_plistActions->begin(); it != m_plistActions->end();)
        {
            if (*it == pAction)
            {
                if (bRelease) (*it)->Release();
                m_plistActions->erase(it++);
                break;
            }
            else ++it;
        }
    }
}
//移除所有行为
void S2SceneNode::StopAllActions(bool bRelease)
{
    if (!m_plistActions)
        return;

    for (auto &it = m_plistActions->begin(); it != m_plistActions->end();)
    {
        if (bRelease) (*it)->Release();
        m_plistActions->erase(it++);
    }
}

////
//获取结点双亲
void S2SceneNode::SetParent(S2SceneNode *pNode)
{
    if (!pNode)
    {
        if (GetParent())
        {
            RemoveFromParent(); 
        }
        m_parent = nullptr;
    }
    else{
        if (this != pNode)
        {
            if (GetParent())
            {
                if (GetParent() != pNode)
                {
                    RemoveFromParent();
                    pNode->AddChild(this);
                }
            }
            else pNode->AddChild(this);
        }
    }
}
S2SceneNode *S2SceneNode::GetParent()const
{
    return m_parent;
}


//设置坐标
void S2SceneNode::SetPosition(int x, int y)
{
    SetPosition(S2Point(x, y));
}
void S2SceneNode::SetPosition(const S2Point &pos)
{
    m_nodePosition.x = pos.x;
    m_nodePosition.y = pos.y;
}
const S2Point &S2SceneNode::GetPosition() const
{
    return m_nodePosition;
}

//取得结点尺寸
void S2SceneNode::SetSize(int width, int height)
{
    SetSize(S2Size(width, height));
}

void S2SceneNode::SetSize(const S2Size &size)
{
    m_nodeSize.width = size.width;
    m_nodeSize.height = size.height;
}
const S2Size &S2SceneNode::GetSize()const
{
    return m_nodeSize;
}
//结点矩形
void S2SceneNode::SetRect(const S2Rect &rt)
{
    SetPosition(rt.left, rt.top);
    SetSize(rt.right - rt.left, rt.bottom - rt.top);
}
S2Rect S2SceneNode::GetRect()const
{
    auto pos = GetPosition();
    auto size = GetSize();
    return S2Rect(pos.x, pos.y, pos.x + size.width, pos.y + size.height);
}
S2Rect S2SceneNode::GetRectWithPos(const S2Point &pos)const
{
    auto size = GetSize();
    return S2Rect(pos.x, pos.y, pos.x + size.width, pos.y + size.height);
}

//设置锚点
void S2SceneNode::SetAnchorPoint(float x, float y)
{
    SetAnchorPoint(S2Vector2(x, y));
}
void S2SceneNode::SetAnchorPoint(const S2Vector2 &pt)
{
    m_anchorPoint = pt;
}
const S2Vector2 &S2SceneNode::GetAnchorPoint() const
{
    return m_anchorPoint;
}


void S2SceneNode::SetWorldMatrix(const S2Matrix *pMat)
{
    if (pMat)m_worldMatrix = *pMat;
    else SMatrixIdentity(&m_worldMatrix);
}
const S2Matrix *S2SceneNode::GetWorldMatrix()const
{
    return &m_worldMatrix;
}

//设置Z序列
void S2SceneNode::SetZOrder(S2Int nZOrder)
{
    m_nZorder = nZOrder;
    if (GetParent())
    {
        GetParent()->__ChangeNodeZOrder(this);
    }

}
S2Int S2SceneNode::GetZOrder() const
{
    return m_nZorder;
}


//设置是否可用
void S2SceneNode::SetEnabled(bool bEnabled)
{
    m_bEnabled = bEnabled;
}
bool S2SceneNode::GetEnabled() const
{
    return m_bEnabled;
}

//设置获取是否可见
void S2SceneNode::SetVisible(bool bVisible)
{
    m_bVisible = bVisible;
}
bool S2SceneNode::GetVisible() const
{
    return m_bVisible;
}
//获取设置用户自定义数据
void S2SceneNode::SetUserData(void *pUserData)
{
    m_pUserData = pUserData;
}
void *S2SceneNode::GetUserData() const
{
    return m_pUserData;
}

//访问节点
void S2SceneNode::Visit(const S2Function<void(S2SceneNode *)> &lam)
{
    lam(this);

    auto list = m_plistChildren;
    if (list && !list->empty())
    {
        auto thisit = list->end();
        for (auto &it = list->begin(); it != list->end();)
        {
            thisit = it++;
            (*thisit)->Visit(lam);
        }
    }
}

S2Point S2SceneNode::ConvertToRelLeftTopPos()const
{
    auto pos = GetPosition();
    auto size = GetSize();
    auto anchorPoint = GetAnchorPoint();
    S2Point pt;

    pt.x = (int)(pos.x - size.width * anchorPoint.x);
    pt.y = (int)(pos.y - size.height * anchorPoint.y);
    return pt;
}

S2Point S2SceneNode::ConvertToAbsLeftTopPos()const
{
    auto pParent = GetParent();
    auto ptPa = pParent ? pParent->ConvertToAbsLeftTopPos() : S2Point(0, 0);
    auto pos = GetPosition();
    auto size = GetSize();
    auto anchorPoint = GetAnchorPoint();
    S2Point pt;

    pt.x = (int)(ptPa.x + pos.x - size.width * anchorPoint.x);
    pt.y = (int)(ptPa.y + pos.y - size.height * anchorPoint.y);
    return pt;
}
S2Point S2SceneNode::ConvertToRelPos()const
{
    return GetPosition();
}
S2Point S2SceneNode::ConvertToAbsPos()const
{
    auto pParent = GetParent();
    auto ptPa = pParent ? pParent->ConvertToAbsPos() : S2Point(0, 0);
    auto pos = GetPosition();
    auto size = GetSize();
    S2Point pt;

    pt.x = (int)(ptPa.x + pos.x);
    pt.y = (int)(ptPa.y + pos.y);
    return pt;
}

///////////
//访问结点
void S2SceneNode::DoVisit()
{
    auto pRenderer = S2Director::GetInstance()->GetRenderView()->GetViewRenderer();
    auto fDelay = (float)(1.0f / S2Director::GetInstance()->GetFramesPerSecond());

    __DoVisit(fDelay, pRenderer, GetWorldMatrix(), true, true);
}

void S2SceneNode::__DoVisit(float fDelay, S2Renderer *pRenderer, const S2Matrix *mat4, bool bUpdate, bool bDraw)
{
    bUpdate = GetEnabled() ? bUpdate : GetEnabled();
    bDraw = GetVisible() ? bDraw : GetVisible();

    if (bUpdate) __OnUpdate(fDelay);
    if (bDraw)  __OnDraw(pRenderer, mat4, 0);

    //访问子结点
    if (m_plistChildren && !m_plistChildren->empty())
    {
        auto thisit = m_plistChildren->end();
        for (auto &it = m_plistChildren->begin(); it != m_plistChildren->end();)
        {
            //FIXME:如果回调的时候执行了AddChild(),会出错??
            thisit = it++;
            (*thisit)->__DoVisit(fDelay, pRenderer, mat4, bUpdate, bDraw);
        }
    }
}


//取得子节点链表
S2List<S2SceneNode *> *S2SceneNode::__GetChildreList()
{
    if (!m_plistChildren)
        m_plistChildren = new S2List<S2SceneNode *>();
    return m_plistChildren;
}

//取得行为链表
S2List<S2Action *> *S2SceneNode::__GetActionsList()
{
    if (!m_plistActions)
        m_plistActions = new S2List<S2Action *>();
    return m_plistActions;
}

//插入链表
void S2SceneNode::__InsertNode(S2SceneNode *pNode, int nZorder)
{
    auto pList = __GetChildreList();
    for (auto &it = pList->begin(); it != pList->end(); ++it)
    {
        if (nZorder < pNode->GetZOrder())
        {
            pList->insert(it, pNode);
            return;
        }
    }
    pList->push_back(pNode);
}

/* 子类调用父类(本类) */
//调整Z序列
void S2SceneNode::__ChangeNodeZOrder(S2SceneNode *pNode)
{
    this->RemoveChild(pNode);
    this->AddChild(this,pNode->GetZOrder());
}

//绘制
void S2SceneNode::__OnDraw(S2Renderer *pRenderer, const S2Matrix *mat4, S2uInt flag)
{
    if (!m_bVisible) 
        return;

    //派生类渲染
    OnDraw(pRenderer, mat4, flag);

}
//逻辑更新
void S2SceneNode::__OnUpdate(float fDelay)
{
    if (!m_bEnabled) 
        return;

    //执行行为
    if (m_plistActions && !m_plistActions->empty())
    {
        auto thisit = m_plistActions->end();
        for (auto &it = m_plistActions->begin(); it != m_plistActions->end();)
        {
            //先保存下一个迭代器,不然会因为回调移除当前迭代器造成找不到下一个迭代器的错误
            thisit = it++;
            (*thisit)->Update(this, fDelay);
        }
    }

    //派生类更新
    OnUpdate(fDelay);
}
