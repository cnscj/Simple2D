#include "SConverer.h"
SConverer::SConverer(void *pObject)
:m_pObject(pObject)
{

}
SConverer::~SConverer()
{

}

void SConverer::Set(void *pObject)
{
    m_pObject = pObject;
}
void *SConverer::Get() const
{
    return m_pObject;
}


