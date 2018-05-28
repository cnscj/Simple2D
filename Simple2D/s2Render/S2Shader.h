/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-03-14 00:00:00 
 * @Brief: 着色器-负责图形特效
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-01 15:04:11
 * @Last Modified log: 
 */

#ifndef _S2SHADER_H_
#define _S2SHADER_H_
#include "../s2Core/S2Object.h"

class S2Renderer;

class S2Shader :public S2Object
{
    friend class S2Renderer;
protected:
    S2Shader(S2Renderer *pRenderer);
    ~S2Shader();
public:
    //从文件中编译
    S2Result CompileShaderFromFile(S2String strFile);
    //从内存中编译
    S2Result CompilseShaderFromMemory(S2cData pAddr,S2uInt len);
public:
    //设置\取得渲染程序
    S2Result SetShaderProgram();
    S2Result GetShaderProgram();  

public:
    //取得渲染器
    S2Renderer *GetRenderer()const;
private:
    S2Renderer      *m_pRenderer;

};
#endif