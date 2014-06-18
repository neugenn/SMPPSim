#ifndef DECIMALVALIDATION_H
#define DECIMALVALIDATION_H

#include "AsciiValidation.h"

namespace SMPP
{
    /*!
     * @brief ASCII Decimal validation algorithm
     */
    class DecimalValidation : public AsciiValidation
    {
    public:
        DecimalValidation();
        virtual ~DecimalValidation();

        /*!
         * @brief Checks if the data from the input buffer is ASCII decimal data
         * @param[in] data Input buffer
         * @param[in] size The size of the input buffer
         */
        virtual bool IsValid(const unsigned char *data, size_t size);

    protected:
        bool IsDecimalDigit(int val) const;
    };
}

#endif // DECIMALVALIDATION_H
