#ifndef _SXDXMATH_H_
#define _SXDXMATH_H_
#include "../s2Core/S2Global.h"
typedef S2Vector3 SXVector3;
typedef S2Matrix SXMatrix;
/* 变换向量,矩阵中间变化连接桥 */

//向量比较
bool SXEuqal(const SXVector3 *pSXVec3, const D3DXVECTOR3 *pDX9Vec3);
bool SXEuqal(const SXMatrix *pSXMat, const D3DXMATRIX *pDX9Mat);

//向量互相转换
void SXVector3ToDX9Vector3(const SXVector3 *pSXVec3, D3DXVECTOR3 *pDX9Vec3);
D3DXVECTOR3 SXVector3ToDX9Vector3(const SXVector3 *pSXVec3);
void DX9Vector3ToSXVector3(const D3DXVECTOR3 *pDX9Vec3, SXVector3 *pSXVec3);
SXVector3 DX9Vector3ToSXVector3(const D3DXVECTOR3 *pDX9Vec3);
//矩阵互相转换
void SXMatrixToDX9Matrix(const SXMatrix *pSXMat, D3DXMATRIX *pDX9Mat);
D3DXMATRIX SXMatrixToDX9Matrix(const SXMatrix *pSXMat);
void DX9MatrixToSXMatrix(const D3DXMATRIX *pDX9Mat, SXMatrix *pSXMat);
SXMatrix DX9MatrixToSXMatrix(const D3DXMATRIX *pDX9Mat);


#endif