/**
*    S2Object
*    @brief 对象结点
*    @author cnscj
*    @link -
*    @version v1.0
*    @date 07/03/2018
*    @update 07/03/2018
*/

#ifndef _S2OBJECT_H_
#define _S2OBJECT_H_
#include "../s2Base/sMemory/SReference.h"
#include "S2Global.h"

class S2Object : public SReference
{
public:
    static const S2uInt FLAG_NONE = 0;
protected:
    S2Object();
    virtual ~S2Object();

public:
    //为对象设置标记
    virtual S2Int GetTag() const;
    virtual void SetTag(S2Int tag);

    //取得对象ID
    S2uInt GetId() const;

    //标识设置
    void SetFlag(S2uInt flag);
    void ChangeFlag(S2uInt flag, bool bState);
    S2uInt GetFlag()const;
public:
    //初始化化
    virtual bool Init();

    //比较函数
    virtual bool Compare(S2Object *pObject);

    //转化为字符串
    virtual S2String ToString();

private:
    S2Int                   m_nTag;                     //对象标记
    S2uInt                  m_unId;                     //对象ID
    S2uInt                  m_unFlag;                   //标识
private:
    static S2uInt           sm_unObjectCount;           //全局对象数量ID自增
};
#endif