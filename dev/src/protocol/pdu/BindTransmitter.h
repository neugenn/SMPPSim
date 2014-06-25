#ifndef BINDTRANSMITTER_H
#define BINDTRANSMITTER_H

#include "Pdu.h"
#include "COctetString.h"

namespace SMPP
{
    /*!
     * @brief BIND_TRANSMITTER PDU
     */
    class BindTransmitter : public Pdu
    {
    public:
        /*!
         * @brief The max lenght of the system_id, including the NULL terminating character
         */
        static const size_t SystemIdMaxLen;

        /*!
         * @brief The max lenght of the password, including the NULL terminating character
         */
        static const size_t PasswordMaxLen;

        /*!
         * @brief The max lenght of the system_type, including the NULL terminating character
         */
        static const size_t SystemTypeMaxLen;

        /*!
         * @brief The max lenght of the address_range, including the NULL terminating character
         */
        static const size_t AddressRangeMaxLen;

        /*!
         * @brief Creates an empty BindTransmitter object
         */
        BindTransmitter();

        /*!
         * @brief Creates a BindTransmitter object from a stream of bytes
         * @param[in] data Host byte order data buffer
         * @param[in] len The length of the data buffer
         * @throw std::invalid_argument The data buffer is NULL
         */
        BindTransmitter(const unsigned char* data, size_t len);

        ~BindTransmitter();

        BindTransmitter(const BindTransmitter& rsh);
        BindTransmitter& operator=(const BindTransmitter& rhs);

        /*!
         * @brief Prepares the formatted content of the BIND_TRANSMITTER_PDU
         * @param[out] s The content of the BIND_TRANSMITTER_PDU
         */
        virtual void GetFormattedContent(std::string &s) const;

        virtual size_t MinSize() const;

        virtual size_t MaxSize() const;

        /*!
         * @brief Data The data in host byte order
         */
        virtual const unsigned char* Data() const;

        /*!
         * @brief The size of the data buffer
         */
        virtual size_t Size() const;

    protected:
        BindTransmitter(const PduHeader& h);
        virtual void GetBodyElements(std::vector<const PduDataType *> &elements) const;

    private:
//        void initBody(const unsigned char* data);

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
