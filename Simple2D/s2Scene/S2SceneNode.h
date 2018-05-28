/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-03-07 00:00:00  
 * @Brief: 场景结点
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-15 11:06:37
 * @Last Modified log: 
 */
#ifndef _S2SCENENODE_H_
#define _S2SCENENODE_H_
#include "../s2Core/S2Node.h"

class S2Director;
class S2Renderer;
class S2Action;

class S2SceneNode :public S2Node
{
    friend class S2Director;
public:
    S2SceneNode();
    virtual ~S2SceneNode();
public:
    //添加子节点
    void AddChild(S2SceneNode *pNode);
    void AddChild(S2SceneNode *pNode,int nZorder);
    //移除结点
    void RemoveChild(S2SceneNode *pNode,bool bRelease = true);
    //从父节点移除
    void RemoveFromParent(bool bRelease = true);
    //移除所有结点
    void RemoveAllChildren(bool bRelease = true);
public:
    //执行行为
    void RunAction(S2Action *pAction);
    //移除行为
    void StopAction(S2Action *pAction, bool bRelease = true);
    //移除所有行为
    void StopAllActions(bool bRelease = true);

public:
    //获取结点双亲
    void SetParent(S2SceneNode *pNode);
    S2SceneNode *GetParent()const;

    //设置相对坐标
    void SetPosition(int x, int y);
    void SetPosition(const S2Point &pt);
    const S2Point &GetPosition() const;

    //取得尺寸
    void SetSize(int width, int height);
    void SetSize(const S2Size &size);
    const S2Size &GetSize() const;

    //获得结点矩形
    void SetRect(const S2Rect &rt);
    S2Rect GetRect()const;
    S2Rect GetRectWithPos(const S2Point &pos)const;

    //设置锚点
    void SetAnchorPoint(float x, float y);
    void SetAnchorPoint(const S2Vector2 &pt);
    const S2Vector2 &GetAnchorPoint() const;

    //变换矩阵
    void SetWorldMatrix(const S2Matrix *pMat);
    const S2Matrix *GetWorldMatrix()const;

    //设置Z序列
    void SetZOrder(S2Int nZOrder);
    S2Int GetZOrder() const;

    //设置是否可用
    void SetEnabled(bool bEnabled);
    bool GetEnabled() const;

    //设置获取是否可见
    void SetVisible(bool bVisible);
    bool GetVisible() const;

    //获取设置用户自定义数据
    void SetUserData(void *pUserData);
    void *GetUserData() const;

    //访问节点
    void Visit(const S2Function<void(S2SceneNode *)> &lam);
public:
    //TODO:坐标系转换
    //S2Point ConvertToLocalSpace(const S2Point *pWorldPoint)const;
    //S2Point ConvertToLocalSpaceWithAR(const S2Point *pWorldPoint)const;
    //S2Point ConvertToWorldSpace(const S2Point *pNodePoint)const;
    //S2Point ConvertToWorldSpaceWithAR(const S2Point *pNodePoint)const;

    S2Point ConvertToRelLeftTopPos()const;
    S2Point ConvertToAbsLeftTopPos()const;
    S2Point ConvertToRelPos()const;
    S2Point ConvertToAbsPos()const;
//public:
//    /* 以下方法由子类负责实现 */
//    //设置旋转
//    virtual void SetRotation(float fRadian){}
//    virtual void SetRotation3D(float x, float y, float z){}
//
//    //水平竖直翻转
//    virtual void SetFlipX(bool bFlip){}
//    virtual void SetFlipY(bool bFlip){}
//
//    //关于XY轴倾斜
//    virtual void SetSkewX(float fSkewX){}
//    virtual void SetSkewY(float fSkewY){}
//
//    //设置缩放比率
//    virtual void SetScale(float fScale){}
//    virtual void SetScaleX(float fScaleX){}
//    virtual void SetScaleY(float fScaleY){}

protected:
    //访问结点
    virtual void DoVisit();
    //绘制节点
    virtual void OnDraw(S2Renderer *pRenderer, const S2Matrix *mat4, S2uInt flag){}
    //逻辑更新
    virtual void OnUpdate(float fDelay){}

private:
    //取得子节点链表
    S2List<S2SceneNode *>    *__GetChildreList();
    //取得行为链表
    S2List<S2Action *>       *__GetActionsList();

    //插入链表
    void __InsertNode(S2SceneNode *pNode,int nZorder);

    //调整Z序列
    void __ChangeNodeZOrder(S2SceneNode *pNode);
    //遍历结点
    void __DoVisit(float fDelay,S2Renderer *pRenderer, const S2Matrix *mat4, bool bUpdate, bool bDraw);
    //绘制
    void __OnDraw(S2Renderer *pRenderer, const S2Matrix *mat4, S2uInt flag);
    //逻辑更新
    void __OnUpdate(float fDelay);
private:
    ///
    S2List<S2SceneNode *>   *m_plistChildren;       //子对象列表
    S2List<S2Action *>      *m_plistActions;        //行为链表

    S2SceneNode         *m_parent;                  //结点双亲
    S2Point             m_nodePosition;             //结点坐标
    S2Size              m_nodeSize;                 //结点大小
    S2Matrix            m_worldMatrix;              //变换矩阵
    S2Vector2           m_anchorPoint;              //锚点
    S2Int               m_nZorder;                  //Z序列

    bool                m_bEnabled;                 //是否可用
    bool                m_bVisible;                 //是否可见

    void                *m_pUserData;               //用户自定义数据

    ///


};
#endif