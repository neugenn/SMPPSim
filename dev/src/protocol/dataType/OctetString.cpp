#include "OctetString.h"

namespace SMPP
{
    OctetString::OctetString(const OctetString& rsh) : data_(NULL), maxSize_(rsh.Size())
    {
        data_ = new unsigned char[maxSize_];
        memcpy(data_, rsh.Data(), maxSize_);
    }

    OctetString& OctetString::operator=(const OctetString& rsh)
    {
        if (&rsh == this)
        {
            return *this;
        }

        if (NULL != data_)
        {
            delete [] data_;
        }

        maxSize_ = rsh.Size();
        data_ = new unsigned char[maxSize_];
        memcpy(data_, rsh.Data(), maxSize_);

        return *this;
    }

    OctetString::OctetString() : data_(NULL), maxSize_(1)
    {
        data_ = new unsigned char[1];
        bzero(data_, 1);
    }

    OctetString::OctetString(const unsigned char* data, size_t maxSize) :
    PduDataType(),
    data_(NULL),
    maxSize_(maxSize)
    {
        if (NULL == data)
        {
            throw std::invalid_argument("NULL data buffer !");
        }

        data_ = new unsigned char[maxSize_];
        memcpy(data_, data, maxSize_);
    }

    OctetString::~OctetString()
    {
        delete [] data_;
    }

    const unsigned char* OctetString::Data() const
    {
        return data_;
    }

    size_t OctetString::Size() const
    {
        return maxSize_;
    }

    bool operator==(const OctetString& lsh, const OctetString& rsh)
    {
        std::string s1;
        PduDataType::GetFormattedData(lsh.Data(), lsh.Size(), s1);

        std::string s2;
        PduDataType::GetFormattedData(rsh.Data(), rsh.Size(), s2);

        return (s1 == s2);
    }

    bool operator!=(const OctetString& lsh, const OctetString& rsh)
    {
        return !(lsh == rsh);
    }
}
