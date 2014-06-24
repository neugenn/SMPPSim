#include "HexValidation.h"

namespace SMPP
{
    HexValidation::HexValidation() : DecimalValidation()
    {}

    HexValidation::~HexValidation()
    {}

    bool HexValidation::IsValid(const unsigned char *data, size_t size) const
    {
        bool res = AsciiValidation::IsValid(data, size);
        for (size_t i = 0; i < size; ++i)
        {
            const int item = static_cast<int>(data[i]);
            if (!this->IsHexDigit(item))
            {
                res = false;
                break;
            }
        }
        return res;
    }

    bool HexValidation::IsHexDigit(int val) const
    {
        return (
            this->IsDecimalDigit(val) ||
            ( (val >= 0x41) && (val <= 0x46) )
              );
    }
}
