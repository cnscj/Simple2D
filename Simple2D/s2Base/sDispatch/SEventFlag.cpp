/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-26 15:56:16 
 * @Brief: Flag类,必须写成cpp文件
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-17 11:20:58
 * @Last Modified log: 
 */
#include "SEventFlag.h"
unsigned int SEventFlag::g_unDispatcherFlag = 0;
unsigned int SEventFlag::GetFlagUID()
{
    return(g_unDispatcherFlag = g_unDispatcherFlag?g_unDispatcherFlag*2:1);
}

bool SEventFlag::HaveFlag(unsigned int x,unsigned int flag)
{
    return (x & flag)?true:false;
}
void SEventFlag::RemoveFlag(unsigned int &x,unsigned int flag)
{
    x = x & ~flag;
}
void SEventFlag::AddFlag(unsigned int &x,unsigned int flag)
{
    x = x|flag;
}
void SEventFlag::SetFlag(unsigned int &x,unsigned int flag,bool state)
{
    state?AddFlag(x,flag):RemoveFlag(x,flag);
}

SEventFlag::SEventFlag()
{

}
SEventFlag::~SEventFlag()
{
    
}

//最多32个flag
const unsigned int SEventFlag::None = 0;                   
const unsigned int SEventFlag::AutoRelease = SEventFlag::GetFlagUID();
const unsigned int SEventFlag::BindUserData = SEventFlag::GetFlagUID();
const unsigned int SEventFlag::ReOrder = SEventFlag::GetFlagUID();
const unsigned int SEventFlag::Delete = SEventFlag::GetFlagUID();
const unsigned int SEventFlag::Remove = SEventFlag::GetFlagUID();
const unsigned int SEventFlag::OnceDelivery = SEventFlag::GetFlagUID();
const unsigned int SEventFlag::Unblock = SEventFlag::GetFlagUID();
//...