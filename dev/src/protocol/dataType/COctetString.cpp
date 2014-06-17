#include "COctetString.h"

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
            throw std::invalid_argument(Name() + "COctetString() : NULL data buffer");
        }

        const char* asciidata = reinterpret_cast<const char*>(data);
        data_ = std::string(asciidata);
        if (data_.size() > len)
        {
            data_ = std::string(asciidata, len - 1);
        }

        if (!validator_.IsValid(this->Data(), this->Size()))
        {
            std::stringstream ss;
            ss << Name() + "COctetString() : Invalid data ! " << data_;
            ss << "Len: " << len;
            throw std::invalid_argument(ss.str());
        }
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
