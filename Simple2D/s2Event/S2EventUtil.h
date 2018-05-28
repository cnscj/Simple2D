/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-04 12:57:22 
 * @Brief: 事件处理实用类
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-04 13:45:47
 * @Last Modified log: 
 */
#ifndef _S2EVENTUTIL_H_
#define _S2EVENTUTIL_H_
#include "../s2Base/sDispatch/SEvent.h"
#include "../s2Core/S2Object.h"
class S2EventUtil : public S2Object
{
public:
    static SEvent::Type GetEventUID();
    static S2uInt GetCommandUID();
private:
    S2EventUtil(){}
    ~S2EventUtil(){}
private:
    static SEvent::Type sm_eventUids;
    static S2uInt sm_commandUids;
};

#endif