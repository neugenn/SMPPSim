#ifndef INTEGER_H_
#define INTEGER_H_

#include "PduDataType.h"
#include <stdexcept>
#include <stdint.h>

namespace SMPP
{
    /*!
     * @brief Unsigned value with the defined number of octets
     */
    template <typename T>
    class Integer : public PduDataType
    {
    public:
        typedef uint64_t value_t;

        /*!
         * @brief The maximum value which can be hold by an Integer object
         */
        static value_t MaxValue();

         /*!
         * @brief Creates an Integer object which is zero filled
         */
        Integer(const char* name = "");

        /*!
         * @brief Creates an Integer object from a stream of bytes
         * @param data Big Endian data buffer used as the value of the Integer object
         * @throw std::invalid_argument Data buffer is NULL
         */
        Integer(const unsigned char*& data, const char* name = "");

       ~Integer();

        /*!
         * @brief BigEndian data buffer
         */
        virtual const unsigned char* Data() const;

        /*!
         * @brief The size of the data buffer
         * @see Data
         */
        virtual size_t Size() const;

        virtual bool IsValid() const;

        /*!
         * @brief Set the value of the integer object
         * @throw std::invalid_argument The value exceeds the maximum allowed
         * @see MaxValue
         */
        void SetValue(value_t val);

        /*!
         * @brief The value of the Integer object
         */
        value_t Value() const;

    private:
        unsigned char data_[sizeof(T)];
    };

    /*!
     * @brief OneByteInteger Unsigned value containing 1 octet
     */
    typedef Integer<unsigned char> OneByteInteger;

    /*!
     * @brief OneByteInteger Unsigned value containing 2 octets
     */
    typedef Integer<uint16_t> TwoByteInteger;

    /*!
     * @brief OneByteInteger Unsigned value containing 4 octets
     */
    typedef Integer<uint32_t> FourByteInteger;
}

#endif // INTEGER_H_
