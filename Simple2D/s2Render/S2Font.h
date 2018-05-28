/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-09 20:27:10 
 * @Brief: 字体类
 * @Last Modified by: cnscj 
 * @Last Modified time: 2018-05-09 20:27:10 
 * @Last Modified log: 
 */

#ifndef _S2FONT_H_
#define _S2FONT_H_
#include "../s2Core/S2Object.h"

class S2Renderer;
class S2Font : public S2Object
{
public:
	S2Font();
	~S2Font();
public:
	//字体名创建
    S2Font *CreateWithFaceName(S2Renderer *pRenderer, S2String faceName, S2uInt height = 10);
public:
	
    template<class T = void*>
    T GetHandle() const
    {
        return static_cast<T>(m_pHandle);
    }
private:
	void *m_pHandle;
};

#endif