/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-19 11:44:52 
 * @Brief: 包装器
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-19 14:09:33
 * @Last Modified log: 
 */
#ifndef _SWRAPPER_H_
#define _SWRAPPER_H_
#include <unordered_map>
#include <string>
#include "SConverer.h"
class SWrapper
{
private:
    class ElementInfo
    {
    public:
        unsigned int unFlag;
        SConverer *pObject;
    };
public:
    SWrapper();
    virtual ~SWrapper();
public:
    void Add(std::string key, void *value, bool bBind = false);
    void Remove(std::string key);
    void RemoveAll();
    SConverer *Get(std::string key);
    
    SConverer *operator[](std::string key);
protected:
    virtual void OnHandle(const ElementInfo &info);
private:
    std::unordered_map<std::string, ElementInfo> m_objectsMap;
};
#endif