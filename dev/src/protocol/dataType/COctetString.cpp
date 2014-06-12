#include "COctetString.h"

namespace SMPP
{
    template <typename T>
    COctetString<T>::COctetString() :
        PduDataType(),
        validator_(T()),
        data_()
    {
    }

    template <typename T>
    COctetString<T>::COctetString(const unsigned char* data) :
    PduDataType(),
    validator_(T()),
    data_()
    {
        if (NULL == data)
        {
            throw std::invalid_argument("COctetString() : NULL data buffer");
        }

        const char* asciidata = reinterpret_cast<const char*>(data);
        data_ = asciidata;

        if (!validator_.IsValid(this->Data(), this->Size()))
        {
            throw std::invalid_argument("COctetString() : Invalid data !");
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

    template class COctetString<AsciiValidation>;
    template class COctetString<DecimalValidation>;
    template class COctetString<HexValidation>;
}
