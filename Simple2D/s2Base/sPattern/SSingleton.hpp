/**
*    SSingleton
*    @brief 单例模式
*    @author cnscj
*    @link -
*    @version v1.0
*    @date 07/03/2018
*    @update 07/03/2018
*/

#ifndef _SSINGLETON_H_
#define _SSINGLETON_H_

template<class T>
class SSingleton
{
private:
    static T* sm_pInstance;        //全局唯一单例
protected:
    SSingleton(T *pInstance = nullptr);
    virtual ~SSingleton();

public:
    //新建全局实例
    static T* NewInstance();

    //获取全局实例
    static T* GetInstance();

    //设置全局实例
    static void SetInstance(T* pInstance);

    //摧毁全局实例
    static void DestroyInstance();
};
template<class T>
T *SSingleton<T>::sm_pInstance = nullptr;        //全局唯一单例

/////
template<class T>
SSingleton<T>::SSingleton(T *pInstance)
{
    SetInstance(pInstance);
}
template<class T>
SSingleton<T>::~SSingleton()
{

}

template<class T>
T *SSingleton<T>::NewInstance()
{
    //FIXME:需要加锁
    if (sm_pInstance == nullptr)
        sm_pInstance = new T();
    else DestroyInstance();
    return GetInstance();
}

template<class T>
void SSingleton<T>::SetInstance(T *pInstance)
{
    if (sm_pInstance == nullptr)
        sm_pInstance = pInstance;
}

template<class T>
T *SSingleton<T>::GetInstance()
{
    if (sm_pInstance == nullptr)
        NewInstance();
    return sm_pInstance;
}
template<class T>
void SSingleton<T>::DestroyInstance()
{
    delete sm_pInstance;
    sm_pInstance = nullptr;
}
#endif