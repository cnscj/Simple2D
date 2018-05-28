/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-03-29 15:45:13 
 * @Brief: 样式类 
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-24 09:48:03
 * @Last Modified log:  
 **/
#ifndef _S2STYLE_H_
#define _S2STYLE_H_
#include "../s2Core/S2Object.h"

class S2Style : public S2Object
{
public:
    S2Function<void()> OnClick;             //点击回调
public:
    S2String    text;                       //文字
    S2uInt      size;                       //大小
    S2ColorRef  color;                      //颜色
    S2uInt      src;                        //图片
    S2Rect      scale9Rect;                 //9Rect
public:
    //默认设置
    virtual void Default();
};

#endif