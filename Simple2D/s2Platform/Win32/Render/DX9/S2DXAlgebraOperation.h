/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-17 15:28:03 
 * @Brief: 
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-17 15:58:37
 * @Last Modified log: 
 */

#ifndef _S2DXALGEBRACONVERTER_H_
#define _S2DXALGEBRACONVERTER_H_
#include "../../../../s2Protocol/S2EngineProtocol.h"
#include "S2DXGlobal.h"
class S2DXAlgebraOperation : public S2AlgebraOperationProtocol<D3DXVECTOR3, D3DXMATRIX>
{
public:
    //向量比较
    bool SVector3Euqal(const S2Vector3 *pSV, const D3DXVECTOR3 *pTV);
    bool SMatrixEuqal(const S2Matrix *pSM, const D3DXMATRIX *pTM);

    //向量互相转换
    D3DXVECTOR3 *S2Vector3ToTVector3(const S2Vector3 *pSV, D3DXVECTOR3 *pTV);
    S2Vector3 *TVector3ToS2Vector3(const D3DXVECTOR3 *pTV, S2Vector3 *pSV);

    //矩阵互相转换
    D3DXMATRIX *S2MatrixToTMatrix(const S2Matrix *pSM, D3DXMATRIX *pTM);
    S2Matrix *TMatrixToS2Matrix(const D3DXMATRIX *pTM, S2Matrix *pSM);
};

#endif