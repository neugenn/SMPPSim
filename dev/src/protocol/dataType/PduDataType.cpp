#include "PduDataType.h"
#include <iomanip>
#include <sstream>
#include <cassert>

namespace SMPP
{
    void PduDataType::GetFormattedData(const unsigned char *data, size_t len, std::string &out)
    {
        assert(NULL != data);

        std::stringstream s;
        for (size_t i = 0; i < len; ++i)
        {
            s << std::setfill('0') << std::setw(2) << std::hex;
            s << (unsigned int)data[i];
        }

        out = s.str();
    }

    std::ostream& operator<<(std::ostream& s, const PduDataType& data)
    {
        std::string res;
        PduDataType::GetFormattedData(data.Data(), data.Size(), res);
        return s << res;
    }
}
