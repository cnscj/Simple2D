/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-24 14:09:52 
 * @Brief: 渲染设备
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-02 21:51:44
 * @Last Modified log: 
 */
#ifndef _S2DEVICE_H_
#define _S2DEVICE_H_
#include "../s2Core/S2Object.h"
class  S2Renderer;
class S2Device : public S2Object
{
    friend class S2Renderer;
public:
    //返回缓冲区宽度
    int GetBufferWidth()const;

    //返回缓冲区高度
    int GetBufferHeight()const;

    //返回缓冲区深度
    int GetBfferDepth()const;

    //取得渲染器
    S2Renderer *GetRenderer()const;
protected:
    S2Device(S2Renderer *pRenderer);
    virtual ~S2Device();
private:
    S2Renderer      *m_pRenderer;
};
#endif