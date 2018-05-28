#include "S2DXAlgebraOperation.h"


//向量比较
bool S2DXAlgebraOperation::SVector3Euqal(const S2Vector3 *pSV, const D3DXVECTOR3 *pTV)
{
    if (
        pSV->x == pTV->x &&
        pSV->y == pTV->y &&
        pSV->z == pTV->z
        )
        return true;
    else return false;
}
bool S2DXAlgebraOperation::SMatrixEuqal(const S2Matrix *pSM, const D3DXMATRIX *pTM)
{
    if (
        pSM->m[0] == pTM->_11 &&
        pSM->m[1] == pTM->_12 &&
        pSM->m[2] == pTM->_13 &&
        pSM->m[3] == pTM->_14 &&

        pSM->m[4] == pTM->_21 &&
        pSM->m[5] == pTM->_22 &&
        pSM->m[6] == pTM->_23 &&
        pSM->m[7] == pTM->_24 &&

        pSM->m[8] == pTM->_31 &&
        pSM->m[9] == pTM->_32 &&
        pSM->m[10] == pTM->_33 &&
        pSM->m[11] == pTM->_34 &&

        pSM->m[12] == pTM->_41 &&
        pSM->m[13] == pTM->_42 &&
        pSM->m[14] == pTM->_43 &&
        pSM->m[15] == pTM->_44
        )
        return true;
    else return false;
}

//向量互相转换
D3DXVECTOR3 *S2DXAlgebraOperation::S2Vector3ToTVector3(const S2Vector3 *pSV, D3DXVECTOR3 *pTV)
{
    pTV->x = pSV->x;
    pTV->y = pSV->y;
    pTV->z = pSV->z;

    return pTV;
}
S2Vector3 *S2DXAlgebraOperation::TVector3ToS2Vector3(const D3DXVECTOR3 *pTV, S2Vector3 *pSV)
{
    pSV->x = pTV->x;
    pSV->y = pTV->y;
    pSV->z = pTV->z;

    return pSV;
}

//矩阵互相转换
D3DXMATRIX *S2DXAlgebraOperation::S2MatrixToTMatrix(const S2Matrix *pSM, D3DXMATRIX *pTM)
{
    pTM->_11 = pSM->m[0];
    pTM->_12 = pSM->m[1];
    pTM->_13 = pSM->m[2];
    pTM->_14 = pSM->m[3];

    pTM->_21 = pSM->m[4];
    pTM->_22 = pSM->m[5];
    pTM->_23 = pSM->m[6];
    pTM->_24 = pSM->m[7];

    pTM->_31 = pSM->m[8];
    pTM->_32 = pSM->m[9];
    pTM->_33 = pSM->m[10];
    pTM->_34 = pSM->m[11];

    pTM->_41 = pSM->m[12];
    pTM->_42 = pSM->m[13];
    pTM->_43 = pSM->m[14];
    pTM->_44 = pSM->m[15];

    return pTM;
}
S2Matrix *S2DXAlgebraOperation::TMatrixToS2Matrix(const D3DXMATRIX *pTM, S2Matrix *pSM)
{
    pSM->m[0] = pTM->_11;
    pSM->m[1] = pTM->_12;
    pSM->m[2] = pTM->_13;
    pSM->m[3] = pTM->_14;

    pSM->m[4] = pTM->_21;
    pSM->m[5] = pTM->_22;
    pSM->m[6] = pTM->_23;
    pSM->m[7] = pTM->_24;

    pSM->m[8] = pTM->_31;
    pSM->m[9] = pTM->_32;
    pSM->m[10] = pTM->_33;
    pSM->m[11] = pTM->_34;

    pSM->m[12] = pTM->_41;
    pSM->m[13] = pTM->_42;
    pSM->m[14] = pTM->_43;
    pSM->m[15] = pTM->_44;

    return pSM;
}
