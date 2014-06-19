#ifndef BINDTRANSMITTERRESP_H
#define BINDTRANSMITTERRESP_H

#include "Pdu.h"
#include "COctetString.h"

namespace SMPP
{
    /*!
     * @brief BIND_TRANSMITTER_RESP PDU
     */
    class BindTransmitterResp : public Pdu
    {
    public:
        /*!
         * @brief The max lenght of the system_id, including the NULL terminating character
         */
        static const size_t SystemIdMaxLen;

        /*!
         * @brief Creates an empty BindTransmitterResp object
         */
        BindTransmitterResp();

        /*!
         * @brief BindTransmitterResp
         * @param data
         * @throw
         */
        BindTransmitterResp(const unsigned char* data);
        ~BindTransmitterResp();

        BindTransmitterResp(const BindTransmitterResp& rsh);
        BindTransmitterResp& operator=(const BindTransmitterResp& rsh);

        virtual void GetBodyInfo(std::string &s) const;
        virtual size_t MinSize() const;
        virtual size_t MaxSize() const;

        virtual const unsigned char* Data() const;
        virtual size_t Size() const;

        void SetSystemId(const std::string& id);
        const std::string& GetSystemId() const;

    private:
        CString systemId_;
        mutable unsigned char* data_;
    };
}

#endif // BINDTRANSMITTERRESP_H
