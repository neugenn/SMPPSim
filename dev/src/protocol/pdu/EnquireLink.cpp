#include "EnquireLink.h"

namespace SMPP
{
    EnquireLink::EnquireLink(const unsigned char* data) :
    Pdu()
    {
        PduHeader* ph = NULL;
        try
        {
            ph = new PduHeader(data);
            this->SetHeader(ph);
            ph = NULL;
        }
        catch (std::exception& e)
        {
            std::stringstream s;
            s << __PRETTY_FUNCTION__ << e.what();
            throw std::invalid_argument(s.str());
        }
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
