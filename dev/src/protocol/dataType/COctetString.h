#ifndef COCTETSTRING_H
#define COCTETSTRING_H

#include "PduDataType.h"
#include "HexValidation.h"
#include <string>
#include <stdexcept>

namespace SMPP
{
    /*!
     * @brief ASCII characters
     */
    template <typename T>
    class COctetString : public PduDataType
    {
    public:
        /*!
         * \brief COctetString Creates an empty string containing only the NULL character
         */
        COctetString();

        /*!
         * @brief COctetString Creates a string object from a raw data buffer
         * @param data The data buffer
         * @throw std::invalid_argument The data buffer is NULL of the data is invalid
         * @see Validation strategy
         */
        COctetString(const unsigned char* data);

        ~COctetString();

        virtual const unsigned char* Data() const;
        virtual size_t Size() const;

    private:
        T validator_;
        std::string data_;
    };

    /*!
     * @brief CString A series of ASCII characters terminated with the NULL character
     */
    typedef COctetString<AsciiValidation> CString;

    /*!
     * @brief CDecimalString A series of ASCII characters, each character representing a decimal digit (0-9) \
     * and terminated with the NULL character
     */
    typedef COctetString<DecimalValidation> CDecimalString;

    /*!
     * @brief CHexString A series of ASCII characters, each character representing a hexadecimal digit (0-F) \
     * and terminated with the NULL character
     */
    typedef COctetString<HexValidation> CHexString;
}

#endif // COCTETSTRING_H
