#include "Pdu.h"

namespace SMPP
{
    Pdu::Pdu() : PduDataType(), header_()
    {
    }

    Pdu::Pdu(const PduHeader& h) : PduDataType(), header_(h)
    {

    }

    Pdu::Pdu(const unsigned char *data) : PduDataType(), header_(data)
    {
    }

    Pdu::~Pdu()
    {}

    const PduHeader& Pdu::GetHeader() const
    {
        return header_;
    }

    PduHeader& Pdu::GetHeader()
    {
        return header_;
    }

    void Pdu::GetBodyInfo(std::string &s) const
    {

    }

    std::ostream& operator<<(std::ostream& s, const Pdu& pdu)
    {
        const PduHeader& h = pdu.GetHeader();
        std::string header;
        h.GetFormattedContent(header);

        std::string body;
        pdu.GetBodyInfo(body);

        s << std::endl;
        s << header;
        s << body;

        return s;
    }
}
