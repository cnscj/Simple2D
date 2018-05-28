/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-07 00:00:00
 * @Brief: 部件基类
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-24 09:58:36
 * @Last Modified log: 
 */

#ifndef _S2WIDGET_H_
#define _S2WIDGET_H_
#include "../s2Core/S2Object.h"
#include "S2Style.h"
class S2DrawEvent;

class S2Widget :public S2Object
{
protected:
    S2Widget();
    virtual ~S2Widget();
protected:
    virtual void OnDraw(S2DrawEvent *);

public:

protected:
    S2Point     m_point;                    //坐标(相对与父节点)
    S2Point     m_anchorPoint;              //锚点
    S2Size      m_size;                     //控件宽高

    S2Style     m_style;                    //样式

};
#endif