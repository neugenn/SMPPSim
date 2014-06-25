#include "Pdu.h"
#include <cassert>

SMPP::FourByteInteger::value_t Pdu::MaxSequenceNumber()
{
    return 0x7FFFFFFF;
}

Pdu::Pdu() : PduDataType(), header_()
{}

Pdu::Pdu(const unsigned char *data) : header_(data)
{}

Pdu::~Pdu()
{
}

SMPP::FourByteInteger::value_t Pdu::CommandLength() const
{
    return header_.CommandLength();
}

SMPP::CommandId Pdu::CommandId() const
{
    return header_.CommandId();
}

SMPP::CommandStatus Pdu::CommandStatus() const
{
    return header_.CommandStatus();
}

void Pdu::SetCommandStatus(SMPP::CommandStatus status)
{
    return header_.SetCommandStatus(status);
}

SMPP::FourByteInteger::value_t Pdu::SequenceNumber() const
{
    return header_.SequenceNumber();
}

void Pdu::SetSequenceNumber(SMPP::FourByteInteger::value_t value)
{
    if (value > Pdu::MaxSequenceNumber())
    {
        throw std::invalid_argument("Sequence number overflow !");
    }

    header_.SetSequenceNumber(value);
}

void Pdu::UpdateCommandLength()
{
    header_.SetCommandLength(this->Size());
}

void Pdu::SetHeader(const PduHeader& h)
{
    header_ = h;
}

bool Pdu::IsValid() const
{
    bool res = false;
    do
    {
        if (!header_.IsValid())
        {
            break;
        }

        const size_t pduSize = this->Size();
        if (pduSize < this->MinSize())
        {
            break;
        }

        if (pduSize > this->MaxSize())
        {
            break;
        }

        res = this->IsValidBody();
    }
    while (false);
    return res;
}

void Pdu::GetFormattedContent(std::string& s) const
{
    header_.GetFormattedContent(s);
}

void Pdu::GetBodyElements(std::vector<const PduDataType *> & /*elements*/) const
{

}

bool Pdu::IsValidBody() const
{
    std::vector<const PduDataType*> elements_;
    this->GetBodyElements(elements_);

    std::vector<const PduDataType*>::const_iterator it = elements_.begin();
    std::vector<const PduDataType*>::const_iterator itEnd = elements_.end();
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

std::ostream& operator<<(std::ostream& s, const Pdu& pdu)
{
    std::string data;
    pdu.GetFormattedContent(data);

    s << data;

    return s;
}
