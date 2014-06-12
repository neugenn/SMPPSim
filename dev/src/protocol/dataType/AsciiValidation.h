#ifndef ASCIIVALIDATION_H
#define ASCIIVALIDATION_H

#include "Validation.h"

namespace SMPP
{
    class AsciiValidation : public Validation
    {
    public:
        AsciiValidation();
        virtual ~AsciiValidation();

        virtual bool IsValid(const unsigned char* data, size_t size);
    };
}

#endif // ASCIIVALIDATION_H
