#include "EnquireLink.h"

namespace SMPP
{
    EnquireLink::EnquireLink(const unsigned char* data) :
    Pdu(data)
    {
    }

    const unsigned char* EnquireLink::Data() const
    {
        return GetHeader().Data();
    }

    size_t EnquireLink::Size() const
    {
        return GetHeader().Size();
    }

    size_t EnquireLink::MinSize() const
    {
        return this->Size();
    }

    size_t EnquireLink::MaxSize() const
    {
        return this->MinSize();
    }
}
