#include "EnquireLinkRes.h"

namespace SMPP
{
    EnquireLinkRes::EnquireLinkRes(const unsigned char* data) : Pdu()
    {
        PduHeader* ph = NULL;
        try
        {
            ph = new PduHeader(data);
            ph->SetCommandId(0x80000015);
            this->SetHeader(ph);
        }
        catch (std::exception& e)
        {
            throw;
        }
    }

    const unsigned char* EnquireLinkRes::Data() const
    {
        return GetHeader().Data();
    }

    size_t EnquireLinkRes::Size() const
    {
        return GetHeader().Size();
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
