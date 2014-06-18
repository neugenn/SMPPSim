#include "PduDataType.h"
#include <iomanip>
#include <sstream>
#include <cassert>

PduDataType::PduDataType() : name_()
{}

const std::string& PduDataType::Name() const
{
    return name_;
}

PduDataType::PduDataType(const char *name) : name_(name)
{
    name_ += " ";
}

std::ostream& operator<<(std::ostream& s, const PduDataType& data)
{
    const unsigned char* buf = data.Data();
    for (size_t i = 0; i < data.Size(); ++i)
    {
        s << std::setfill('0') << std::setw(2) << std::uppercase << std::hex;
        s << static_cast<unsigned int>(buf[i]);
    }
    return s;
}

bool operator==(const PduDataType& lsh, const PduDataType& rsh)
{
    const bool equalSizes = (lsh.Size() == rsh.Size());
    const bool equalData = (0 == memcmp(lsh.Data(), rsh.Data(), lsh.Size()));

    return (equalSizes && equalData);
}

bool operator!=(const PduDataType& lsh, const PduDataType& rsh)
{
    return (!(lsh == rsh));
}
