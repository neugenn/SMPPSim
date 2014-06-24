#include "DecimalValidation.h"

namespace SMPP
{
    DecimalValidation::DecimalValidation() : AsciiValidation()
    {}

    DecimalValidation::~DecimalValidation()
    {}

    bool DecimalValidation::IsDecimalDigit(int val) const
    {
        return ( (val >= 0x30) && (val <= 0x39) );
    }

    bool DecimalValidation::IsValid(const unsigned char *data, size_t size) const
    {
        bool res = AsciiValidation::IsValid(data, size);

        for (size_t i = 0; i < size; ++i)
        {
            const int item = static_cast<int>(data[i]);
            if (!this->IsDecimalDigit(item))
            {
                res = false;
                break;
            }
        }

        return res;
    }
}
