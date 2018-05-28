/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-23 17:37:25 
 * @Brief: 纹理类
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-20 16:34:49
 * @Last Modified log: 
 */
#ifndef _S2TEXTURE_H_
#define _S2TEXTURE_H_
#include "../s2Core/S2Object.h"

class S2Renderer;

class S2Texture : public S2Object
{
public:
    S2Texture();
    ~S2Texture();
public:
    S2Texture *CreateWithFile(S2Renderer *pRenderer, S2String file);
    S2Texture *CreateWithResource(S2Renderer *pRenderer, S2uInt unRcid);
    S2Texture *CreateWithMemory(S2Renderer *pRenderer, const S2Data pAddr, S2uInt len);

public:
    //取得纹理加载文件像素的宽高(实际宽高)
    S2uInt GetWidth()const;
    S2uInt GetHeight()const;
    
    //取得纹理suface宽高(非实际宽高)
    S2uInt GetSurfaceWidth()const;
    S2uInt GetSurfaceHeight()const;
public:
    template<class T = void*>
    T GetHandle() const
    {
        return static_cast<T>(m_pHandle);
    }
private:
    void    *m_pHandle;         //纹理句柄
    S2uInt  m_nPixelWidth;      //宽
    S2uInt  m_nPixelHeight;     //高
};
#endif