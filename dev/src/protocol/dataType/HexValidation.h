#ifndef HEXVALIDATION_H
#define HEXVALIDATION_H

#include "DecimalValidation.h"

namespace SMPP
{
    class HexValidation : public DecimalValidation
    {
    public:
        HexValidation();
        ~HexValidation();

        virtual bool IsValid(const unsigned char *data, size_t size);
    private:
        bool IsHexDigit(int val) const;
    };
}

#endif // HEXVALIDATION_H
