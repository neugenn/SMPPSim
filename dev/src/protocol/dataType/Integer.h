#ifndef INTEGER_H_
#define INTEGER_H_

#include "PduDataType.h"
#include <stdexcept>

namespace SMPP
{
    /*!
     * @brief Unsigned value with the defined number of octets
     */
    template <size_t T>
    class Integer : public PduDataType
    {
    public:
         /*!
         * @brief Creates an Integer object which is zero filled
         */
        Integer();

        /*!
         * @brief Creates an Integer object
         * @param data Data buffer used as the value of the Integer object
         * @throw std::invalid_argument Data buffer is NULL
         */
        explicit Integer(const unsigned char* data);

       ~Integer();

        virtual const unsigned char* Data() const;
        virtual size_t Size() const;

    private:
        unsigned char data_[T];
    };

    /*!
     * @brief OneByteInteger Unsigned value containing 1 octet
     */
    typedef Integer<size_t(1)> OneByteInteger;

    /*!
     * @brief OneByteInteger Unsigned value containing 2 octets
     */
    typedef Integer<size_t(2)> TwoByteInteger;

    /*!
     * @brief OneByteInteger Unsigned value containing 4 octets
     */
    typedef Integer<size_t(4)> FourByteInteger;
}

#endif // INTEGER_H_
