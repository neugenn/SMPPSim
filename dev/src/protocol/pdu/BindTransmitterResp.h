#ifndef BINDTRANSMITTERRESP_H
#define BINDTRANSMITTERRESP_H

#include "Pdu.h"
#include "COctetString.h"

namespace SMPP
{
    class BindTransmitterResp : public Pdu
    {
    public:
        static const size_t SystemIdLen = 16; //bytes

        BindTransmitterResp();
        BindTransmitterResp(const unsigned char* data, size_t len);
        ~BindTransmitterResp();

        virtual void GetBodyInfo(std::string &s) const;
        virtual const unsigned char* Data() const;
        virtual size_t Size() const;
        void SetSystemId(const std::string& id);

    private:
        void UpdateCommandLen();

    private:
        CString systemId_;
    };
}

#endif // BINDTRANSMITTERRESP_H
