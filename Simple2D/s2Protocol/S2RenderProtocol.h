/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-19 15:19:07 
 * @Brief: 渲染协议文件
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-19 15:27:59
 * @Last Modified log: 
 */
#ifndef _S2RENDERPROTOCAL_H_
#define _S2RENDERPROTOCAL_H_
#include "../s2Core/S2Global.h"


/**
 * @brief 视图协议
 * 
 */
class S2ViewProtocol
{
public:
    /**
    * @brief 取得View的名称
    *
    * @return S2String
    */
    S2String GetViewName()const;

    /**
    * @brief 取得VIew的宽
    *
    * @return S2uInt
    */
    S2uInt  GetViewWidth()const;

    /**
    * @brief 取得View的高
    *
    * @return S2uInt
    */
    S2uInt  GetViewHeight()const;

    /**
    * @brief 是否窗口化
    *
    * @return true
    * @return false
    */
    bool IsWindowed()const;
};


/**
 * @brief 渲染器协议
 * 
 */
class S2RendererProtocol
{
public:
    /**
    * @brief 开始渲染
    *
    * @return S2Result
    */
    virtual S2Result BeginRander() = 0;

    /**
    * @brief 结束渲染
    *
    * @return S2Result
    */
    virtual S2Result EndRender() = 0;
};

/**
 * @brief 设备驱动协议
 * 
 */
class S2DeviceProtocol
{
public:

};

/**
 * @brief 着色器协议
 * 
 */
class S2ShaderProtocol
{
public:

};
/**
* @brief 纹理协议
*
*/
class S2TextureProtocol
{
public:
    /**
    * @brief 取得纹理表面宽度
    *
    * @return S2uInt
    */
    S2uInt GetSurfaceWidth()const;

    /**
    * @brief 取得纹理表面高度
    *
    * @return S2uInt
    */
    S2uInt GetSurfaceHeight()const;

   /* 
    S2Result CreateWithFile(S2RendererProtocol *pRenderer, S2String file);
    S2Result CreateWithResource(S2RendererProtocol *pRenderer, S2uInt unRcid);
    S2Result CreateWithMemory(S2RendererProtocol *pRenderer, const S2Data pAddr, S2uInt len);
   */
};

/**
 * @brief 2D纹理协议
 * 
 */
class S2Texture2DProtocol :public S2TextureProtocol
{
public:
    /**
    * @brief 取得纹理宽度
    *
    * @return S2uInt
    */
    virtual S2uInt GetWidth() = 0;

    /**
    * @brief 取得纹理高度
    *
    * @return S2uInt
    */
    virtual S2uInt GetHeight() = 0;
};

/**
 * @brief 字体协议
 * 
 */
class S2FontProtocol
{

};

#endif