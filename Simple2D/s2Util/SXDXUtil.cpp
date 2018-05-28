#include "SXDXUtil.h"

///////////////////////////////////////
bool SXEuqal(const SXVector3 *pSXVec3, const D3DXVECTOR3 *pDX9Vec3)
{
    if (
        pSXVec3->x == pDX9Vec3->x &&
        pSXVec3->y == pDX9Vec3->y &&
        pSXVec3->z == pDX9Vec3->z
        )
        return true;
    else return false;
}
bool SXEuqal(const SXMatrix *pSXMat, const D3DXMATRIX *pDX9Mat)
{
    if (
        pSXMat->m[0] == pDX9Mat->_11 &&
        pSXMat->m[1] == pDX9Mat->_12 &&
        pSXMat->m[2] == pDX9Mat->_13 &&
        pSXMat->m[3] == pDX9Mat->_14 &&

        pSXMat->m[4] == pDX9Mat->_21 &&
        pSXMat->m[5] == pDX9Mat->_22 &&
        pSXMat->m[6] == pDX9Mat->_23 &&
        pSXMat->m[7] == pDX9Mat->_24 &&

        pSXMat->m[8] == pDX9Mat->_31 &&
        pSXMat->m[9] == pDX9Mat->_32 &&
        pSXMat->m[10] == pDX9Mat->_33 &&
        pSXMat->m[11] == pDX9Mat->_34 &&

        pSXMat->m[12] == pDX9Mat->_41 &&
        pSXMat->m[13] == pDX9Mat->_42 &&
        pSXMat->m[14] == pDX9Mat->_43 &&
        pSXMat->m[15] == pDX9Mat->_44
        )
        return true;
    else return false;
}

void SXVector3ToDX9Vector3(const SXVector3 *pSXVec3, D3DXVECTOR3 *pDX9Vec3)
{
    pDX9Vec3->x = pSXVec3->x;
    pDX9Vec3->y = pSXVec3->y;
    pDX9Vec3->z = pSXVec3->z;
}

D3DXVECTOR3 SXVector3ToDX9Vector3(const SXVector3 *pSXVec3)
{
    D3DXVECTOR3 ve3;
    SXVector3ToDX9Vector3(pSXVec3, &ve3);
    return ve3;
}

void SXMatrixToDX9Matrix(const SXMatrix *pSXMat, D3DXMATRIX *pDX9Mat)
{
    pDX9Mat->_11 = pSXMat->m[0];
    pDX9Mat->_12 = pSXMat->m[1];
    pDX9Mat->_13 = pSXMat->m[2];
    pDX9Mat->_14 = pSXMat->m[3];

    pDX9Mat->_21 = pSXMat->m[4];
    pDX9Mat->_22 = pSXMat->m[5];
    pDX9Mat->_23 = pSXMat->m[6];
    pDX9Mat->_24 = pSXMat->m[7];

    pDX9Mat->_31 = pSXMat->m[8];
    pDX9Mat->_32 = pSXMat->m[9];
    pDX9Mat->_33 = pSXMat->m[10];
    pDX9Mat->_34 = pSXMat->m[11];

    pDX9Mat->_41 = pSXMat->m[12];
    pDX9Mat->_42 = pSXMat->m[13];
    pDX9Mat->_43 = pSXMat->m[14];
    pDX9Mat->_44 = pSXMat->m[15];
}

D3DXMATRIX SXMatrixToDX9Matrix(const SXMatrix *pSXMat)
{
    D3DXMATRIX mat;
    SXMatrixToDX9Matrix(pSXMat, &mat);
    return mat;
}

void DX9Vector3ToSXVector3(const D3DXVECTOR3 *pDX9Vec3, SXVector3 *pSXVec3)
{
    pSXVec3->x = pDX9Vec3->x;
    pSXVec3->y = pDX9Vec3->y;
    pSXVec3->z = pDX9Vec3->z;
}
SXVector3 DX9Vector3ToSXVector3(const D3DXVECTOR3 *pDX9Vec3)
{
    SXVector3 ve3;
    DX9Vector3ToSXVector3(pDX9Vec3, &ve3);
    return ve3;
}

void DX9MatrixToSXMatrix(const D3DXMATRIX *pDX9Mat, SXMatrix *pSXMat)
{
    pSXMat->m[0] = pDX9Mat->_11;
    pSXMat->m[1] = pDX9Mat->_12;
    pSXMat->m[2] = pDX9Mat->_13;
    pSXMat->m[3] = pDX9Mat->_14;

    pSXMat->m[4] = pDX9Mat->_21;
    pSXMat->m[5] = pDX9Mat->_22;
    pSXMat->m[6] = pDX9Mat->_23;
    pSXMat->m[7] = pDX9Mat->_24;

    pSXMat->m[8] = pDX9Mat->_31;
    pSXMat->m[9] = pDX9Mat->_32;
    pSXMat->m[10] = pDX9Mat->_33;
    pSXMat->m[11] = pDX9Mat->_34;

    pSXMat->m[12] = pDX9Mat->_41;
    pSXMat->m[13] = pDX9Mat->_42;
    pSXMat->m[14] = pDX9Mat->_43;
    pSXMat->m[15] = pDX9Mat->_44;

}
SXMatrix DX9MatrixToSXMatrix(const D3DXMATRIX *pDX9Mat)
{
    SXMatrix mat;
    DX9MatrixToSXMatrix(pDX9Mat, &mat);
    return mat;
}
