#include "COctetString.h"
#include <iomanip>

namespace SMPP
{
    template <typename T>
    COctetString<T>::COctetString(const char* name) :
        PduDataType(name),
        validator_(T()),
        data_()
    {
    }

    template <typename T>
    COctetString<T>::COctetString(const unsigned char* data, size_t len, const char* name) :
    PduDataType(name),
    validator_(T()),
    data_()
    {
        if (NULL == data)
        {
            std::stringstream s;
            s << __PRETTY_FUNCTION__ << " " << this->Name();
            s << " : NULL data buffer !";
            throw std::invalid_argument(s.str());
        }

        const char* asciidata = reinterpret_cast<const char*>(data);
        data_ = std::string(asciidata);
        if (data_.size() >= len)
        {
            data_ = std::string(asciidata, len - 1);
        }

        /*
        if (!validator_.IsValid(this->Data(), this->Size()))
        {
            std::stringstream ss;
            ss << __PRETTY_FUNCTION__ << " " << this->Name();
            ss << " : Invalid ASCII data ! (";
            for (size_t i = 0; i < data_.size(); ++i)
            {
                ss << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << static_cast<int>(data_[i]);
            }
            ss << ") len: " << data_.size();
            throw std::invalid_argument(ss.str());
        }
        */
    }

    template <typename T>
    COctetString<T>::~COctetString()
    {}

    template <typename T>
    const unsigned char* COctetString<T>::Data() const
    {
        return reinterpret_cast<const unsigned char*>(data_.c_str());
    }

    template <typename T>
    size_t COctetString<T>::Size() const
    {
        return data_.size() + 1;
    }

    template <typename T>
    bool COctetString<T>::IsValid()
    {
        return (validator_.IsValid(this->Data(), this->Size()));
    }

    template <typename T>
    const std::string& COctetString<T>::Value() const
    {
        return data_;
    }

    template <typename T>
    void COctetString<T>::SetValue(std::string &value)
    {
        data_ = value;
        validator_.IsValid(this->Data(), this->Size());
    }

    template class COctetString<AsciiValidation>;
    template class COctetString<DecimalValidation>;
    template class COctetString<HexValidation>;
}
