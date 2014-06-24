#include "EnquireLinkRes.h"

namespace SMPP
{
    EnquireLinkRes::EnquireLinkRes(const unsigned char* data) : Pdu(data)
    {
    }

    const unsigned char* EnquireLinkRes::Data() const
    {
        return header_.Data();
    }

    size_t EnquireLinkRes::Size() const
    {
        return header_.Size();
    }

    size_t EnquireLinkRes::MinSize() const
    {
        return this->Size();
    }

    size_t EnquireLinkRes::MaxSize() const
    {
        return this->MinSize();
    }
}
