#include "AsciiValidation.h"
#include <cassert>

namespace SMPP
{
    AsciiValidation::AsciiValidation() : Validation()
    {}

    AsciiValidation::~AsciiValidation()
    {}

    bool AsciiValidation::IsValid(const unsigned char* data, size_t size)
    {
        assert(NULL != data);

        bool res = true;
        for (size_t i = 0; i < size; ++i)
        {
            if (static_cast<int>(data[i]) > 0x7F)
            {
                res = false;
                break;
            }
        }

        return res;
    }
}
