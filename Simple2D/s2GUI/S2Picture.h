/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-11 14:10:34 
 * @Brief: 图片控件
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-11 14:15:42
 * @Last Modified log: 
 */
#ifndef _S2PICTURE_H_
#define _S2Picture_H_
#include "S2Control.h"

class S2Picture : public S2Control
{
public:
    //加载图片
    void Load(S2String file);
    void LoadFromData(S2Byte ptr,S2uInt len,S2uInt format = 0);

    //保存图片
    void Save(S2String path);
    
    //设置变换
    void Transformed(const S2Matrix *mat4,S2uInt flag);
public:
    //获取\设置图片宽高
    S2Size GetSize();
    void SetSize(int width,int height);
    
private:
 
};

#endif