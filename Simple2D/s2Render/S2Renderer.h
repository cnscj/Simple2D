/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-03-14 00:00:00 
 * @Brief: 渲染器
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-02 21:41:12
 * @Last Modified log: 
 */

#ifndef _S2RENDERER_H_
#define _S2RENDERER_H_
#include "../s2Core/S2Object.h"

class S2View;

class S2Graphics;
class S2Painter;
class S2Effect;

class S2Shader;
class S2Device;

class S2Texture;
class S2Font;

class S2Renderer : public S2Object
{
    friend class S2View;
public:
    //矩阵变换状态类型
    enum class TransformStateType
    {
        World,       //世界转换
        View,        //视窗转换
        Proj,        //投影转换
    };
protected:
    S2Renderer();
    ~S2Renderer();
public:
    S2Result CreateWithView(S2View *pView);

public:
    //设置世界变换矩阵
    S2Result SetTransform(TransformStateType type,const S2Matrix *mat);
    S2Result GetTransform(TransformStateType type, S2Matrix *mat)const;
public:
    //根据文件创建纹理
    S2Texture *CreateTextureWithFile(S2String file);
    S2Texture *CreateTextureWithResource(S2uInt unRcid);
    S2Texture *CreateTextureWithMemory(const S2Data pAddr,S2uInt len);

    //根据格式创建字体
    S2Font *CreateFontWithFaceName(S2String strFacename, S2uInt height=15);
public:
    S2Graphics *CreateGraphics();
    S2Painter *CreatePainter();
    S2Effect *CreateEffect();

public:
    //取得渲染视图
    S2View   *GetView() const;

    //取得着色器
    S2Shader *GetShader() const;

    //取得渲染设备
    S2Device *GetDevice() const;

    //取得渲染设备句柄
    template<class T = void*> 
    T GetDeviceHandle() const
    {
        return static_cast<T>(m_pDeviceHandle); 
    }
public:
    //开始渲染
    S2Result BeginRender();

    //结束渲染
    S2Result EndRender();

private:
    void        *m_pDeviceHandle;           //渲染设备句柄

    S2View      *m_pView;                   //所属视图

    S2Shader    *m_pShader;                 //着色器
    S2Device    *m_pDevice;                 //渲染设备

    S2Graphics  *m_pGraphics;               //图像渲染器
    S2Painter   *m_pPainter;                //图形渲染器 
    S2Effect    *m_pEffect;                 //特效渲染器

    int          m_nRenderReqTimes;         //渲染请求次数

};
#endif