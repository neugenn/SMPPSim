#ifndef PDU_H
#define PDU_H

#include "PduDataType.h"
#include "PduHeader.h"
#include <string>

namespace SMPP
{
    class Pdu : public PduDataType
    {
    public:
        Pdu();
        Pdu(const PduHeader& h);
        Pdu(const unsigned char* data);
        virtual ~Pdu();

        const PduHeader& GetHeader() const;
        PduHeader& GetHeader();
        virtual void GetBodyInfo(std::string& s) const;

    protected:
        PduHeader header_;
    };

    std::ostream& operator<<(std::ostream& s, const Pdu& pdu);
}

#endif // PDU_H
