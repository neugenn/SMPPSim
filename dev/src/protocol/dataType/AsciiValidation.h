#ifndef ASCIIVALIDATION_H
#define ASCIIVALIDATION_H

#include "Validation.h"

namespace SMPP
{
    /*!
     * @brief ASCII Validation algorithm
     */
    class AsciiValidation : public Validation
    {
    public:
        AsciiValidation();
        virtual ~AsciiValidation();

        /*!
         * @brief Checks if the data from the input buffer is ASCII data
         * @param[in] data Input buffer
         * @param[in] size The size of the input buffer
         */
        virtual bool IsValid(const unsigned char* data, size_t size) const;
    };
}

#endif // ASCIIVALIDATION_H
