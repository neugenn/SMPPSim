#ifndef BINDTRANSMITTER_H
#define BINDTRANSMITTER_H

#include "Pdu.h"
#include "COctetString.h"

namespace SMPP
{
    class BindTransmitter : public Pdu
    {
    public:
        static const size_t SystemIdLen = 16; //bytes
        static const size_t PasswordLen = 9;
        static const size_t SystemTypeLen = 13;
        static const size_t AddressRangeLen = 41;

        BindTransmitter();
        BindTransmitter(const unsigned char* data, size_t len);
        ~BindTransmitter();

        BindTransmitter(const BindTransmitter& lsh);

        virtual void GetBodyInfo(std::string &s) const;
        virtual const unsigned char* Data() const;
        virtual size_t Size() const;

    private:
        void initBody(const unsigned char* data, size_t len);

    private:
        CString systemId_;
        CString password_;
        CString systemType_;
        OneByteInteger interfaceVersion_;
        OneByteInteger addrTon_;
        OneByteInteger addrNpi_;
        CString addressRange_;
        mutable const unsigned char* data_;
    };
}

#endif // BINDTRANSMITTER_H
