/**
*
*    SRunnable接口类
*    SThread的接口
*    @author ZeroX
*    @version v1.0 22/07/2017(22/07/2017)
*
*/

#ifndef _SRUNNABLE_H_
#define _SRUNNABLE_H_

class SRunnable
{
protected:
    virtual ~SRunnable() {};
public:
    //逻辑事件函数,子类重写此函数
    virtual void Run() = 0;
};

#endif