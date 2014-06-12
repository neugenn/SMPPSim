#ifndef PDUHEADER_H
#define PDUHEADER_H

#include <ostream>
#include "Integer.h"

namespace SMPP
{
    class PduHeader : public PduDataType
    {
    public:
        PduHeader(const unsigned char* dataBuf);

        virtual const unsigned char* Data() const;
        virtual size_t Size() const;

        const SMPP::FourByteInteger& CommandLength() const;
        const SMPP::FourByteInteger& CommandId() const;
        const SMPP::FourByteInteger& CommandStatus() const;
        const SMPP::FourByteInteger& SequenceNumber() const;

    private:
        static const size_t HeaderSize = 16; //bytes
        void init(const unsigned char* data);

    private:
        SMPP::FourByteInteger commandLen_;
        SMPP::FourByteInteger commandId_;
        SMPP::FourByteInteger commandStatus_;
        SMPP::FourByteInteger sequenceNum_;
        mutable unsigned char data_[HeaderSize];
    };

    std::ostream& operator<<(std::ostream& s, const PduHeader& data);
}

#endif // PDUHEADER_H
