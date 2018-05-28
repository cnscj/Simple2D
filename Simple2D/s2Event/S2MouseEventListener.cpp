#include "S2MouseEventListener.h"
#include "S2MouseEvent.h"
#include "S2EventTable.h"
S2MousemEventListener::S2MousemEventListener()
:S2BaseEventListener(S2EventTable::System::MouseEvent)
{

}
S2MousemEventListener::~S2MousemEventListener()
{

}

void S2MousemEventListener::OnEvent(SEvent *pEvent)
{
    S2MouseEvent *e = static_cast<S2MouseEvent *>(pEvent);
    S2MouseEvent::Type  type = e->eType;
    switch (type)
    {
        case S2MouseEvent::Type::Dowm:
        {
            this->OnMouseDown(e);
        }break;
        case S2MouseEvent::Type::Move:
        {
            this->OnMouseMove(e);
        }break;
        case S2MouseEvent::Type::Up:
        {
            this->OnMouseUp(e);
        }break;
        case S2MouseEvent::Type::Scroll:
        {
            this->OnMouseScroll(e);
        }break;
    }
}
