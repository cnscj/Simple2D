/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-24 09:36:09 
 * @Brief: 
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-04-24 09:41:03
 * @Last Modified log: 
 */

#ifndef _S2BUTTONSTYLE_H_
#define _S2BUTTONSTYLE_H_
#include "S2Style.h"

class S2ButtonStyle : public S2Style
{
public:
    S2Style normal;
    S2Style press;
    S2Style release;
};

#endif