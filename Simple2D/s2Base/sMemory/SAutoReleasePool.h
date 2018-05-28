/**
*    SAutoReleasePool
*    @brief 自释放对象池-生命周期为1帧
*    @author ZEROX
*    @link -
*    @version v1.1
*    @date 11/18/2017
*    @update 11/18/2017
*/
#ifndef _SAUTORELEASEPOOL_H_
#define _SAUTORELEASEPOOL_H_
#include <list>
#include "SPool.h"
class SAutoReleasePool :public SPool
{
public:
    SAutoReleasePool();
    ~SAutoReleasePool();
public:
    // 将对象添加到自动释放池
    void AddObject(SReference *pRef);

    // 将对象从自动释放池中移除  
    void RemoveObject(SReference *pRef);

    // 将自动释放池中的对象释放掉
    void Clear();

    //清理池
    void Purge();
private:
    //引用对象列表
    ///注意CCArray内部是通过将对象retain 然后存储起来的，应用计数会增加1 
    std::list<SReference *>    *m_pObjectArray;
    
};

#endif