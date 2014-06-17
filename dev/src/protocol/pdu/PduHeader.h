#ifndef PDUHEADER_H
#define PDUHEADER_H

#include "Integer.h"

namespace SMPP
{
    class PduHeader : public PduDataType
    {
    public:
        PduHeader();
        PduHeader(const unsigned char* dataBuf);

        virtual const unsigned char* Data() const;
        virtual size_t Size() const;

        uint32_t GetCommandLength() const;
        void SetCommandLength(uint32_t len);

        uint32_t GetCommandId() const;
        void SetCommandId(uint32_t len);

        const SMPP::FourByteInteger& CommandStatus() const;

        uint32_t GetSequenceNumber() const;
        void SetSequenceNumber(uint32_t value);

        void GetFormattedContent(std::string& res) const;

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
}

#endif // PDUHEADER_H
