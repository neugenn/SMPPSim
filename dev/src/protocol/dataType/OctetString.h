#ifndef OCTETSTRING_H
#define OCTETSTRING_H

#include <stdexcept>
#include "PduDataType.h"

namespace SMPP
{
    /*!
     * @brief A series of octets, not necessarily NULL terminated
     */
    class OctetString : public PduDataType
    {
    public:
        /*!
         * @brief Creates an octet string object containing of a single character with the value 0x00
         */
        OctetString(const char* name = "");

        /*!
         * @brief Creates an octet sring object from the provided data buffer
         * @param data The data buffer
         * @param maxSize The size of the data buffer
         * @throw std::invalid_argument The data buffer is NULL
         */
        OctetString(const unsigned char*& data, size_t maxSize, const char* name = "");

        OctetString(const OctetString&);
        OctetString& operator=(const OctetString&);
        ~OctetString();

        virtual const unsigned char* Data() const;
        virtual size_t Size() const;
        virtual bool IsValid() const;

    private:
        unsigned char* data_;
        size_t maxSize_;
    };
}

#endif // OCTETSTRING_H
