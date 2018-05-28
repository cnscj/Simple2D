#include "SPoolManager.h"
SPoolManager *SPoolManager::g_pPoolManager = NULL;

//取得实例
SPoolManager *SPoolManager::GetInstance()
{
    if (!g_pPoolManager)
       g_pPoolManager = new SPoolManager();
    return g_pPoolManager;
}

//销毁实例
void SPoolManager::DestroyInstance()
{
    delete g_pPoolManager;
    g_pPoolManager = NULL;
}
////////
SPoolManager::SPoolManager()
{
  
}
SPoolManager::~SPoolManager()
{


}
