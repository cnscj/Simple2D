/**
*    S2Layer
*    @brief 层类
*    @author cnscj
*    @link -
*    @version v1.0
*    @date 09/03/2018
*    @update 09/03/2018
*/

#ifndef _S2LAYER_H_
#define _S2LAYER_H_
#include "S2SceneNode.h"

class S2Layer :public S2SceneNode
{
protected:
    /*  */
    //鼠标弹起
    virtual bool OnTouchDown(){return true;}

    //鼠标移动
    virtual bool OnTouchMove(){return true;}

    //鼠标弹起
    virtual bool OnTouchUp(){return true;}
};
#endif