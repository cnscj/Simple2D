/**
*    SAutoReleasePoolManager
*    @brief 自动释放池管理池
*    @author cocos2d
*    @link -
*    @version v1.1
*    @date 11/18/2017
*    @update 11/18/2017
*/

#ifndef _SAUTORELEASEPOOLMANAGER_H_
#define _SAUTORELEASEPOOLMANAGER_H_
#include <list>
#include "SAutoReleasePool.h"

class SAutoReleasePoolManager
{
public:
    SAutoReleasePoolManager();
    ~SAutoReleasePoolManager();
public:
    //取得实例
    static SAutoReleasePoolManager *GetInstance();

    //销毁实例
    static void DestroyInstance();
public:
    //添加对象
    void AddObject(SReference *pRef);

    //移除对象
    void RemoveObject(SReference *pRef);

    // 清空所有的自动释放池  
    void Finalize();

    // 增加一个自动释放池  
    void Push();

    // 移除一个自动释放池，即移除当前自动释放池  
    void Pop();
public:
    //清理池-每帧都要调用
    void Purge();

private:
    //取得当前自动释放池
    SAutoReleasePool *GetCurReleasePool();
private:
    //唯一实例
    static SAutoReleasePoolManager      *g_pPoolManager;

    //用于存放自动释放池的队列 
    std::list<SAutoReleasePool *>       *m_pAutoReleasePoolStack;    
    //指向自动释放池队列的末尾节点
    SAutoReleasePool                    *m_pCurReleasePool;            
};
#endif