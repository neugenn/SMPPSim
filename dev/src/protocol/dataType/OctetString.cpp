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

    OctetString::OctetString(const char* name) : PduDataType(name), data_(NULL), maxSize_(1)
    {
        data_ = new unsigned char[1];
        bzero(data_, 1);
    }

    OctetString::OctetString(const unsigned char*& data, size_t maxSize, const char* name) :
    PduDataType(name),
    data_(NULL),
    maxSize_(maxSize)
    {
        if (NULL == data)
        {
            std::stringstream s;
            s << __PRETTY_FUNCTION__ << " " << this->Name();
            s << " : NULL data buffer !";
            throw std::invalid_argument(s.str());
        }

        data_ = new unsigned char[maxSize_];
        memcpy(data_, data, maxSize_);

        data += maxSize;
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

    bool OctetString::IsValid() const
    {
        return true;
    }
}
