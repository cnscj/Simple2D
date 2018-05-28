/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-06 15:23:59 
 * @Brief: 按钮类
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-11 15:05:00
 * @Last Modified log: 
 */

#ifndef _S2BUTTON_H_
#define _S2BUTTON_H_
#include "S2Control.h"

class S2Button : public S2Control
{
public:
    //设置\获取按钮文字
    void SetText(S2String text);
    const S2String &GetText();
public:
    S2Function<void()> &OnClick = m_style.OnClick;
private:

};
#endif