/**
*    SObserver
*    @brief 观察者模式-主题
*    @author cnscj
*    @link -
*    @version v1.0
*    @date 07/03/2018
*    @update 07/03/2018
*/

#ifndef _SOBSERVER_H_
#define _SOBSERVER_H_

class SSubject;

class SObserver
{
public:
    //观察者更新数据
    void Update(SSubject *pSubject, void *date);
};
void SObserver::Update(SSubject *pSubject, void *date)
{

}
#endif