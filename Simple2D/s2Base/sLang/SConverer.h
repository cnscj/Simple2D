/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-19 12:47:29 
 * @Brief: 类型转换器
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-19 13:23:11
 * @Last Modified log: 
 */
#ifndef _SCONVERER_H_
#define _SCONVERER_H_

class SConverer
{
public:
    SConverer(void *pObject = nullptr);
    virtual ~SConverer();
public:
    void Set(void *pObject);
    void *Get()const;
public:
    template<class T = void> 
    T *To() const
    {
        return static_cast<T*>(m_pObject); 
    }
private:
    void *m_pObject;
};

#endif
