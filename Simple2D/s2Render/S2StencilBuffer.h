/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-01 14:54:36 
 * @Brief: 模板缓存
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-08 22:12:54
 * @Last Modified log: 
 */
#ifndef _S2STENCILBUFFER_H_
#define _S2STENCILBUFFER_H_
#include "../s2Core/S2Object.h"
class  S2Renderer;
class S2StencilBuffer : public S2Object
{
    friend class S2Renderer;
public:
    //取得渲染器
    S2Renderer *GetRenderer()const;
protected:
    S2StencilBuffer(S2Renderer *pRenderer);
    ~S2StencilBuffer();
private:
    S2Renderer      *m_pRenderer;
};
#endif