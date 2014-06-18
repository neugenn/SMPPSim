#ifndef HEXVALIDATION_H
#define HEXVALIDATION_H

#include "DecimalValidation.h"

namespace SMPP
{
    /*!
     * @brief ASCII Hexadecimal validation algorithm
     */
    class HexValidation : public DecimalValidation
    {
    public:
        HexValidation();
        ~HexValidation();

        /*!
         * @brief Checks if the data from the input buffer is ASCII hexadecimal data
         * @param[in] data Input buffer
         * @param[in] size The size of the input buffer
         */
        virtual bool IsValid(const unsigned char *data, size_t size);
    private:
        bool IsHexDigit(int val) const;
    };
}

#endif // HEXVALIDATION_H
