/**
*    SSubject
*    @brief 观察者模式-主题
*    @author cnscj
*    @link -
*    @version v1.0
*    @date 07/03/2018
*    @update 07/03/2018
*/

#ifndef _SSUBJECT_H_
#define _SSUBJECT_H_
#include <vector>
#include "SObserver.hpp"

class SSubject
{
public:
    //添加,删除观察者
    void AddObserver(SObserver *pObserver);
    void DeleteObserver(SObserver *pObserver);

    //主题数据是否发生改变
    bool HasChanged();

    //通知观察者更新数据
    void NotifyObserver(void *data);
    void NotifyObservers();
protected:
    //设置主题变化标志
    void SetChanged(bool bChange = true);

    //清除主题变化变化标志
    void ClearChanged();
protected:
    SSubject();
    virtual~SSubject();
private:
    std::vector<SObserver *> m_Obs;
    bool m_bChanged;
};
void SSubject::AddObserver(SObserver *pObserver)
{
    if (pObserver)
        m_Obs.push_back(pObserver);
}
void SSubject::DeleteObserver(SObserver *pObserver)
{
    if (pObserver){
        for (auto &it = m_Obs.begin(); it != m_Obs.end(); it++){
            if (*it == pObserver){
                m_Obs.erase(it);
                break;
            }
        }
    }
}

bool SSubject::HasChanged()
{
    return m_bChanged;
}

void SSubject::NotifyObserver(void *data)
{
    for (auto &it : m_Obs){
        it->Update(this, data);
    }
}
void SSubject::NotifyObservers()
{
    for (auto &it : m_Obs){
        it->Update(this, nullptr);
    }
}

void SSubject::SetChanged(bool bChange)
{
    m_bChanged = bChange;
}
void SSubject::ClearChanged()
{
    m_bChanged = false;
}
#endif