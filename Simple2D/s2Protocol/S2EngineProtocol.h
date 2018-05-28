/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-19 15:18:44 
 * @Brief: 引擎类协议文件
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-26 12:33:09
 * @Last Modified log: 
 */
#ifndef _S2ENGINEPROTOCOL_H_
#define _S2ENGINEPROTOCOL_H_
#include "../s2Core/S2Global.h"
/**
 * @brief 应用程序协议
 * 
 */
class S2ApplicationProtocol
{
public:
    /**
     * @brief 完成启动时调用
     * 
     * @return true 
     * @return false 
     */
    virtual bool ApplicationFinishLaunching() = 0;

    /**
     * @brief 进入后台调用
     * 
     */
    virtual void ApplicationEnterBackground() = 0;

    /**
     * @brief 从后台恢复到前台调用
     * 
     */
    virtual void ApplicationEnterForeground() = 0;
};



/**
 * @brief 线性代数运算协议
 * 
 * @tparam TVec3 3维向量类型
 * @tparam TMat4 4维矩阵类型
 */
template<typename TVec3, typename TMat4>
class S2AlgebraOperationProtocol
{
public:
    /**
    * @brief 两向量比较
    *
    * @param pSV S数学库中的Vec3
    * @param pTV T数学库中的Vec3
    * @return true
    * @return false
    */
    virtual bool SVector3Euqal(const S2Vector3 *pSV, const TVec3 *pTV) = 0;
    /**
    * @brief 两矩阵比较
    *
    * @param pSM S数学库中的Mat4
    * @param pTM T数学库中的Mat4
    * @return true
    * @return false
    */
    virtual bool SMatrixEuqal(const S2Matrix *pSM, const TMat4 *pTM) = 0;

    /**
    * @brief S库中的Vec3转为T库中的Vec3
    *
    * @param pSV S数学库中的Vec3
    * @param pTV T数学库中的Vec3
    * @return TVec3* T数学库中的Vec3
    */
    virtual TVec3 *S2Vector3ToTVector3(const S2Vector3 *pSV, TVec3 *pTV) = 0;
    /**
    * @brief T库中的Vec3转为S库中的Vec3
    *
    * @param pTV T数学库中的Vec3
    * @param pSV S数学库中的Vec3
    * @return S2Vector3* S数学库中的Vec3
    */
    virtual S2Vector3 *TVector3ToS2Vector3(const TVec3 *pTV, S2Vector3 *pSV) = 0;

    /**
    * @brief S库中的Mat4转为T库中的Mat4
    *
    * @param pSM S数学库中的Mat4
    * @param pTM T数学库中的Mat4
    * @return TMat4* T数学库中的Mat4
    */
    virtual TMat4 *S2MatrixToTMatrix(const S2Matrix *pSM, TMat4 *pTM) = 0;
    /**
    * @brief T库中的Mat4转为S库中的Mat4
    *
    * @param pTM T数学库中的Mat4
    * @param pSM S数学库中的Mat4
    * @return S2Matrix* S数学库中的Mat4
    */
    virtual S2Matrix *TMatrixToS2Matrix(const TMat4 *pTM, S2Matrix *pSM) = 0;

    //////////////
public:

};

#endif