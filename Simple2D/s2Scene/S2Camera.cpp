#include "S2Camera.h"
#include "../s2Render/S2Renderer.h"
#include "../s2Base/sMath/SMathX.hpp"

S2Camera::S2Camera()
{
    m_vRightVector = S2Vector3(1.0f, 0.0f, 0.0f);				// 默认右向量与X正半轴重合
    m_vUpVector = S2Vector3(0.0f, 1.0f, 0.0f);					// 默认上向量与Y正半轴重合
    m_vLookVector = S2Vector3(0.0f, 0.0f, 1.0f);				// 默认观察向量与Z正半轴重合
    m_vCameraPosition = S2Vector3(0.0f, 0.0f, -50.0f);			// 默认摄像机坐标为(0.0f, 0.0f, -50.0f)
    m_vTargetPosition = S2Vector3(0.0f, 0.0f, 0.0f);			// 默认观察目标位置为(0.0f, 0.0f, 0.0f);

    SetViewMatrix();											// 设置取景变换矩阵
    SetProjMatrix();											// 设置投影变换矩阵
}

S2Camera::~S2Camera()
{

}

///////////
//计算取景变换矩阵
S2Matrix *S2Camera::CalculateViewMatrix(S2Matrix *pMatrix)
{
    //1.先把3个向量都规范化并使其相互垂直，成为一组正交矩阵
    SVec3Normalize(&m_vLookVector, &m_vLookVector);                     // 规范化观察分量
    SVec3Cross(&m_vUpVector, &m_vLookVector, &m_vRightVector);          // 上向量与观察向量垂直
    SVec3Normalize(&m_vUpVector, &m_vUpVector);							// 规范化上向量
    SVec3Cross(&m_vRightVector, &m_vUpVector, &m_vLookVector);          // 右向量与上向量垂直
    SVec3Normalize(&m_vRightVector, &m_vRightVector);                   // 规范化右向量


    // 2.创建出取景变换矩阵
    //依次写出取景变换矩阵的第一行
    pMatrix->_11 = m_vRightVector.x;           // Rx
    pMatrix->_12 = m_vUpVector.x;              // Ux
    pMatrix->_13 = m_vLookVector.x;            // Lx
    pMatrix->_14 = 0.0f;
    //依次写出取景变换矩阵的第二行
    pMatrix->_21 = m_vRightVector.y;           // Ry
    pMatrix->_22 = m_vUpVector.y;              // Uy
    pMatrix->_23 = m_vLookVector.y;            // Ly
    pMatrix->_24 = 0.0f;
    //依次写出取景变换矩阵的第三行
    pMatrix->_31 = m_vRightVector.z;           // Rz
    pMatrix->_32 = m_vUpVector.z;              // Uz
    pMatrix->_33 = m_vLookVector.z;            // Lz
    pMatrix->_34 = 0.0f;
    //依次写出取景变换矩阵的第四行
    pMatrix->_41 = -(float)SVec3Dot(&m_vRightVector, &m_vCameraPosition);    // -P*R
    pMatrix->_42 = -(float)SVec3Dot(&m_vUpVector, &m_vCameraPosition);       // -P*U
    pMatrix->_43 = -(float)SVec3Dot(&m_vLookVector, &m_vCameraPosition);     // -P*L
    pMatrix->_44 = 1.0f;

    return pMatrix;
}
S2Matrix *S2Camera::CalculateProjMatrix(S2Matrix *pMatrix, float fovy, float Aspect, float zn, float zf)
{
    float yScale = 1 / tan(fovy / 2);
    float xScale = yScale / Aspect;

    pMatrix->_11 = xScale;
    pMatrix->_12 = 0;
    pMatrix->_13 = 0;
    pMatrix->_14 = 0;

    pMatrix->_21 = 0;
    pMatrix->_22 = yScale;
    pMatrix->_23 = 0;
    pMatrix->_24 = 0;

    pMatrix->_31 = 0;
    pMatrix->_32 = 0;
    pMatrix->_33 = zf / (zf - zn);
    pMatrix->_34 = 1;

    pMatrix->_41 = 0;
    pMatrix->_42 = 0;
    pMatrix->_43 = -zn * zf / (zf - zn);
    pMatrix->_44 = 0;

    return pMatrix;
}

////////////////////
//三个Get系列函数

//返回当前摄像机位置矩阵
void S2Camera::GetCameraPosition(S2Vector3 *pVector)
{
    *pVector = m_vCameraPosition;
}

//返回当前的观察矩阵
void S2Camera::GetLookVector(S2Vector3 *pVector)
{
    *pVector = m_vLookVector;
}

void S2Camera::GetViewMatrix(S2Matrix *pMatrix)
{
    *pMatrix = m_matView;
}
void S2Camera::GetProjMatrix(S2Matrix *pMatrix)
{
    *pMatrix = m_matProj;
}

//四个Set系列函数，注意他们参数都有默认值NULL的，调用时不写参数也可以
//设置摄像机的目标观察位置向量
void S2Camera::SetTargetPosition(S2Vector3 *pLookat)
{
    //先看看pLookat是否为默认值NULL
    if (pLookat != nullptr)  m_vTargetPosition = (*pLookat);
    else m_vTargetPosition = S2Vector3(0.0f, 0.0f, 0.0f);

    m_vLookVector = m_vTargetPosition - m_vCameraPosition;//观察点位置减摄像机位置，得到观察方向向量
    SVec3Normalize(&m_vLookVector, &m_vLookVector);//规范化m_vLookVector向量

    //正交并规范化m_vUpVector和m_vRightVector
    SVec3Cross(&m_vUpVector, &m_vLookVector, &m_vRightVector);
    SVec3Normalize(&m_vUpVector, &m_vUpVector);
    SVec3Cross(&m_vRightVector, &m_vUpVector, &m_vLookVector);
    SVec3Normalize(&m_vRightVector, &m_vRightVector);
}
//设置摄像机所在的位置向量
void S2Camera::SetCameraPosition(S2Vector3 *pVector)
{
    S2Vector3 V = S2Vector3(0.0f, 0.0f, -100.0f);
    m_vCameraPosition = pVector ? (*pVector) : V;//三目运算符，如果pVector为真的话，
    //返回*pVector的值（即m_vCameraPosition=*pVector），
    //否则返回V的值（即m_vCameraPosition=V）
}
//设置取景变换矩阵
void S2Camera::SetViewMatrix(S2Matrix *pMatrix)
{
    //根据pMatrix的值先做一下判断
    if (pMatrix) m_matView = *pMatrix;
    else CalculateViewMatrix(&m_matView);
    //把取景变换矩阵的值分下来分别给右分量，上分量，和观察分量
    m_vRightVector = S2Vector3(m_matView._11, m_matView._12, m_matView._13);
    m_vUpVector = S2Vector3(m_matView._21, m_matView._22, m_matView._23);
    m_vLookVector = S2Vector3(m_matView._31, m_matView._32, m_matView._33);
}
//设置投影变换矩阵
void S2Camera::SetProjMatrix(S2Matrix *pMatrix)
{
    //判断值有没有，没有的话就计算一下
    if (pMatrix != nullptr)m_matProj = *pMatrix;
    else CalculateProjMatrix(&m_matProj,3.14f/4.0f ,800.f/ 600.f);  
}


// 沿right向量移动
void S2Camera::MoveAlongRight(float fUnits)
{
    //直接乘以fUnits的量来累加就行了
    m_vCameraPosition += m_vRightVector * fUnits;
    m_vTargetPosition += m_vRightVector * fUnits;
}
// 沿up向量移动
void S2Camera::MoveAlongUp(float fUnits)
{
    //直接乘以fUnits的量来累加就行了
    m_vCameraPosition += m_vUpVector * fUnits;
    m_vTargetPosition += m_vUpVector * fUnits;
}
// 沿look向量移动
void S2Camera::MoveAlongLook(float fUnits)
{
    //直接乘以fUnits的量来累加就行了
    m_vCameraPosition += m_vLookVector * fUnits;
    m_vTargetPosition += m_vLookVector * fUnits;
}

// 绕各分量旋转的三个函数
// 绕right向量旋转
void S2Camera::RotationRight(float fRadian)
{
    S2Matrix R;
    SMatrixRotationAxis(&R, &m_vRightVector, fRadian);                          //创建出绕m_vRightVector旋转fRadian个弧度的R矩阵
    SVec3TransformCoord(&m_vUpVector, &m_vUpVector, &R);                        //让m_vUpVector向量绕m_vRightVector旋转fRadian个弧度
    SVec3TransformCoord(&m_vLookVector, &m_vLookVector, &R);                    //让m_vLookVector向量绕m_vRightVector旋转fRadian个弧度

    m_vTargetPosition = m_vLookVector * (float)SVec3Length(&m_vCameraPosition);//更新一下观察点的新位置（方向乘以模=向量）
}

// 绕up向量旋转
void S2Camera::RotationUp(float fRadian)
{
    //飞行模式下的绕轴
    S2Matrix R;
    SMatrixRotationAxis(&R, &m_vUpVector, fRadian);                             //创建出绕m_vUpVector旋转fRadian个弧度的R矩阵
    SVec3TransformCoord(&m_vRightVector, &m_vRightVector, &R);                  //让m_vRightVector向量绕m_vUpVector旋转fRadian个弧度
    SVec3TransformCoord(&m_vLookVector, &m_vLookVector, &R);                    //让m_vLookVector向量绕m_vUpVector旋转fRadian个弧度

    m_vTargetPosition = m_vLookVector * (float)SVec3Length(&m_vCameraPosition);//更新一下观察点的新位置（方向乘以模=向量）
    
}

// 绕look向量旋转
void S2Camera::RotationLook(float fRadian)
{
    //S2Matrix R;
    //SXMatrixRotationAxis(&R, &m_vLookVector, fRadian);                            //创建出绕m_vLookVector旋转fRadian个弧度的R矩阵
    //SXVec3TransformCoord(&m_vRightVector, &m_vRightVector, &R);                   //让m_vRightVector向量绕m_vLookVector旋转fRadian个弧度
    //SXVec3TransformCoord(&m_vUpVector, &m_vUpVector, &R);                         //让m_vUpVector向量绕m_vLookVector旋转fRadian个弧度

    //m_vTargetPosition = m_vLookVector * (float)SXVec3Length(&m_vCameraPosition);  //更新一下观察点的新位置（方向乘以模=向量）

    S2Matrix R;
    float length = (float)SVec3Length(&(m_vTargetPosition - m_vCameraPosition));
    SMatrixRotationY(&R, fRadian);
    //左右旋转的时候一般情况下只能绕着世界坐标Y轴转而不是本地Y -- m_vRightVector，避免X方向产生Y坐标，导致地面倾斜，这个可以作为地震崩塌之类的特效吧，呵呵  
    SVec3TransformCoord(&m_vUpVector, &m_vUpVector, &R);
    SVec3TransformCoord(&m_vLookVector, &m_vLookVector, &R);
    SVec3TransformCoord(&m_vRightVector, &m_vRightVector, &R);

    m_vTargetPosition = m_vCameraPosition + m_vLookVector * length;
}

//更新摄像机
void S2Camera::Update(S2Renderer *pRenderer)
{
    CalculateViewMatrix(&m_matView);
    pRenderer->SetTransform(S2Renderer::TransformStateType::View, &m_matView);
    pRenderer->SetTransform(S2Renderer::TransformStateType::Proj, &m_matProj);
}

