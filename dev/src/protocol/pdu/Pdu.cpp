#include "Pdu.h"
#include <cassert>

Pdu::Pdu() : PduDataType(), header_(NULL)
{}

Pdu::~Pdu()
{
    if (NULL != header_)
    {
        delete header_;
    }
}

Pdu::Pdu(const Pdu &rsh) : header_(new PduHeader(rsh.GetHeader()))
{}

Pdu& Pdu::operator=(const Pdu& rsh)
{
    if (NULL != header_)
    {
        delete header_;
    }

    header_ = new PduHeader(rsh.GetHeader());
    return *this;
}

const PduHeader& Pdu::GetHeader() const
{
    assert(NULL != header_);
    return *header_;
}

void Pdu::SetSequenceNumber(uint32_t value)
{
    assert(NULL != header_);
    header_->SetSequenceNumber(value);
}

void Pdu::SetCommandStatus(uint32_t status)
{
    assert(NULL != header_);
    header_->SetCommandStatus(status);
}

void Pdu::UpdateCommandLength()
{
    assert(NULL != header_);
    header_->SetCommandLength(this->Size());
}

void Pdu::SetHeader(PduHeader *&h)
{
    if (NULL != header_)
    {
        delete header_;
    }
    header_ = h;
    h = NULL;
}

std::ostream& operator<<(std::ostream& s, const Pdu& pdu)
{
    const PduHeader& h = pdu.GetHeader();
    std::string header;
    h.GetFormattedContent(header);

    std::string body;
    pdu.GetBodyInfo(body);

    s << header;
    s << body;

    return s;
}
