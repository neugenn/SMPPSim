#include "Pdu.h"
#include <cassert>

Pdu::Pdu() : PduDataType(), header_()
{}

Pdu::Pdu(const unsigned char *data) : header_(data)
{}

Pdu::~Pdu()
{
}

/*
Pdu::Pdu(const Pdu &rsh) : header_(rsh.GetHeader())
{}

Pdu& Pdu::operator=(const Pdu& rsh)
{
    if (this == &rsh)
    {
        return *this;
    }

    header_ = PduHeader(rsh.GetHeader());
    return *this;
}
*/

const PduHeader& Pdu::GetHeader() const
{
    return header_;
}

void Pdu::SetSequenceNumber(uint32_t value)
{
    header_.SetSequenceNumber(value);
}

void Pdu::SetCommandStatus(uint32_t status)
{
    header_.SetCommandStatus(status);
}

void Pdu::UpdateCommandLength()
{
    header_.SetCommandLength(this->Size());
}

void Pdu::SetHeader(const PduHeader& h)
{
    header_ = h;
}

bool Pdu::IsValid()
{
    if (!header_.IsValid())
    {
        return false;
    }

    std::vector<PduDataType*> elements_;
    this->GetBodyElements(elements_);

    std::vector<PduDataType*>::const_iterator it = elements_.begin();
    std::vector<PduDataType*>::const_iterator itEnd = elements_.end();
    bool res = true;
    for (; it != itEnd; ++it)
    {
        if (!(*it)->IsValid())
        {
            res = false;
            break;
        }
    }

    return res;
}

void Pdu::GetFormattedContent(std::string& s) const
{
    header_.GetFormattedContent(s);
}

void Pdu::GetBodyElements(std::vector<PduDataType *>& /*elements*/)
{

}

std::ostream& operator<<(std::ostream& s, const Pdu& pdu)
{
    std::string data;
    pdu.GetFormattedContent(data);

    s << data;

    return s;
}
