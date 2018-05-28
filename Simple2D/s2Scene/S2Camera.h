/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-03-07 00:00:00
 * @Brief: 摄像机类
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-15 18:08:15
 * @Last Modified log: 
 */

#ifndef _S2CAMERA_H_
#define _S2CAMERA_H_
#include "../S2Core/S2Object.h"

class S2Renderer;
class S2Camera :public S2Object
{
public:
    S2Camera();
    virtual ~S2Camera();
public:
    //二个计算取景变换的函数
    S2Matrix *CalculateViewMatrix(S2Matrix *pMatrix);                         // 计算取景变换矩阵
    S2Matrix *CalculateProjMatrix(S2Matrix *pMatrix, float fovy, float Aspect, float zn = 1.0f, float zf = 300000.0f);       // 计算投影变换矩阵

    // 四个Get系列函数
    void GetCameraPosition(S2Vector3 *pVector);                               // 返回当前摄像机位置矩阵
    void GetLookVector(S2Vector3 *pVector);                                   // 返回当前的观察矩阵
    void GetViewMatrix(S2Matrix *pMatrix);                                    // 返回当前变换矩阵
    void GetProjMatrix(S2Matrix *pMatrix);                                    // 返回当前变换矩阵

    // 四个Set系列函数，注意他们参数都有默认值nullptr的，调用时不写参数也可以
    void SetTargetPosition(S2Vector3 *pLookat = nullptr);                     // 设置摄像机的目标观察位置向量
    void SetCameraPosition(S2Vector3 *pVector = nullptr);                     // 设置摄像机所在的位置向量
    void SetViewMatrix(S2Matrix *pMatrix = nullptr);                          // 设置取景变换矩阵
    void SetProjMatrix(S2Matrix *pMatrix = nullptr);                          // 设置投影变换矩阵

    // 摄像机移动
    virtual void MoveAlongRight(float fUnits);                                // 沿right向量移动
    virtual void MoveAlongUp(float fUnits);                                   // 沿up向量移动
    virtual void MoveAlongLook(float fUnits);                                 // 沿look向量移动

    // 绕各分量旋转的三个函数
    virtual void RotationRight(float fRadian);                                 // 绕right向量旋转
    virtual void RotationUp(float fRadian);                                    // 绕up向量旋转
    virtual void RotationLook(float fRadian);                                  // 绕look向量旋转

    virtual void Update(S2Renderer *pRenderer);                               // 数据更新
protected:
    S2Vector3    m_vRightVector;            // 右分量向量
    S2Vector3    m_vUpVector;               // 上分量向量
    S2Vector3    m_vLookVector;             // 观察方向向量
    S2Vector3    m_vCameraPosition;         // 摄像机位置的向量
    S2Vector3    m_vTargetPosition;         // 目标观察位置的向量
    S2Matrix     m_matView;                 // 取景变换矩阵
    S2Matrix     m_matProj;                 // 投影变换矩阵

};
#endif