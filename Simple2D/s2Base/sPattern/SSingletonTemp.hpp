/**
*    SSingletonTemp
*    @brief 单例模式
*    @author cnscj
*    @link -
*    @version v1.0
*    @date 07/03/2018
*    @update 07/03/2018
*/

#ifndef _SSINGLETONTEMP_H_
#define _SSINGLETONTEMP_H_

template<class T>
class SSingletonTemp
{
private:
    static T* sm_pInstance;        //全局唯一单例
protected:
    SSingletonTemp(T *pInstance = nullptr);
    virtual ~SSingletonTemp();

public:

    //获取全局实例
    static T* GetInstance();

    //设置全局实例
    static void SetInstance(T* pInstance);

    //摧毁全局实例
    static void DestroyInstance();
};
template<class T>
T *SSingletonTemp<T>::sm_pInstance = nullptr;        //全局唯一单例

/////
template<class T>
SSingletonTemp<T>::SSingletonTemp(T *pInstance)
{
    SetInstance(pInstance);
}
template<class T>
SSingletonTemp<T>::~SSingletonTemp()
{

}

template<class T>
void SSingletonTemp<T>::SetInstance(T *pInstance)
{
    if (sm_pInstance == nullptr)
        sm_pInstance = pInstance;
}

template<class T>
T *SSingletonTemp<T>::GetInstance()
{
    return sm_pInstance;
}
template<class T>
void SSingletonTemp<T>::DestroyInstance()
{
    if (sm_pInstance)
    {
        delete sm_pInstance;
        sm_pInstance = nullptr;
    }

}
#endif