/**
*    SPoolManager
*    @brief 对象管理池
*    @author cocos2d
*    @link -
*    @version v1.1
*    @date 11/18/2017
*    @update 11/18/2017
*/

#ifndef _SPOOLMANAGER_H_
#define _SPOOLMANAGER_H_
#include <list>
#include "SAutoReleasePool.h"

class SPoolManager
{

public:
    SPoolManager();
    ~SPoolManager();
public:
    //取得实例
    static SPoolManager *GetInstance();

    //销毁实例
    static void DestroyInstance();

private:
    //唯一实例
    static SPoolManager                *g_pPoolManager;
    
};
#endif