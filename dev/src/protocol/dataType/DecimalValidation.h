#ifndef DECIMALVALIDATION_H
#define DECIMALVALIDATION_H

#include "AsciiValidation.h"

namespace SMPP
{
    class DecimalValidation : public AsciiValidation
    {
    public:
        DecimalValidation();
        virtual ~DecimalValidation();

        virtual bool IsValid(const unsigned char *data, size_t size);

    protected:
        bool IsDecimalDigit(int val) const;
    };
}

#endif // DECIMALVALIDATION_H
