/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-24 09:36:09 
 * @Brief: 
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-24 09:49:39
 * @Last Modified log: 
 */

#ifndef _S2LABELSTYLE_H_
#define _S2LABELSTYLE_H_
#include "S2Style.h"

class S2LabelStyle : public S2Style
{
public:
    S2Int           outline;
    S2ColorRef      outlineColor;
};

#endif