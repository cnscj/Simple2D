/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-26 09:49:42 
 * @Brief: Flag配置文件
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-17 11:21:13
 * @Last Modified log: 
 */

#ifndef _SEVENTFLAG_H_
#define _SEVENTFLAG_H_
class SEventFlag
{

public:
    //判断是否存在flag
    static bool HaveFlag(unsigned int x,unsigned int flag);
    //移除某个或多个flag
    static void RemoveFlag(unsigned int &x,unsigned int flag);
    //添加某个或多个flag
    static void AddFlag(unsigned int &x,unsigned int flag);
    //将某个或多个flag设置为state
    static void SetFlag(unsigned int &x,unsigned int flag,bool state);
public: 
    //最多32个flag
    static const unsigned int None;                //无标志
    static const unsigned int AutoRelease;         //自释放
    static const unsigned int BindUserData;        //绑定用户数据
    static const unsigned int ReOrder;             //重排
    static const unsigned int Delete;              //删除
    static const unsigned int Remove;              //移除
    static const unsigned int OnceDelivery;        //一次交付
    static const unsigned int Unblock;             //非阻塞信息
    //...

    
private:
    SEventFlag();
    ~SEventFlag();
private:
    static unsigned int g_unDispatcherFlag;
    static unsigned int GetFlagUID();
};
#endif