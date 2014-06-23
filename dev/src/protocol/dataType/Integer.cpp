#include "Integer.h"
#include <arpa/inet.h>
#include <limits>

namespace SMPP
{
    template <typename T>
    T SwapBytes(T val)
    {
        return val;
    }

    template<>
    uint16_t SwapBytes(uint16_t val)
    {
        return htons(val);
    }

    template<>
    uint32_t SwapBytes(uint32_t val)
    {
        return htonl(val);
    }

    template <typename T>
    typename Integer<T>::value_t Integer<T>::MaxValue()
    {
        return std::numeric_limits<T>::max();
    }

    template <typename T>
    Integer<T>::Integer(const unsigned char* data, const char* name) : PduDataType(name)
    {
        if (NULL == data)
        {
            std::stringstream s;
            s << __PRETTY_FUNCTION__ << " " << Name();
            s << " : NULL data buffer !";
            throw std::invalid_argument(s.str());
        }

        bzero(&data_[0], sizeof(T));
        memcpy(&data_[0], data, sizeof(T));
    }

    template <typename T>
    Integer<T>::Integer(const char* name) : PduDataType(name)
    {
        bzero(&data_[0], sizeof(T));
    }

    template <typename T>
    Integer<T>::~Integer() {}

    template <typename T>
    const unsigned char* Integer<T>::Data() const
    {
        return &data_[0];
    }

    template <typename T>
    size_t Integer<T>::Size() const
    {
        return sizeof(T);
    }

    template <typename T>
    bool Integer<T>::IsValid()
    {
        return true;
    }

    template <typename T>
    void Integer<T>::SetValue(value_t val)
    {
        const T theValue = T(val);
        if (value_t(theValue) < val)
        {
            std::stringstream s;
            s << __PRETTY_FUNCTION__ << " " << Name();
            s << " : value(" << val << ") bigger than the maximum allowed value(" << MaxValue() << ")";
            throw std::invalid_argument(s.str());
        }

        const T newVal =  SwapBytes<T>(theValue);
        const unsigned char* buf = reinterpret_cast<const unsigned char*>(&newVal);
        memcpy(&data_[0], buf, sizeof(newVal));
    }

    template <typename T>
    typename Integer<T>::value_t Integer<T>::Value() const
    {
        T val = T(0);
        const unsigned char* buf = reinterpret_cast<const unsigned char*>(&data_[0]);
        memcpy(&val, buf, sizeof(T));
        return SwapBytes<T>(val);
    }

    template class Integer<unsigned char>;
    template class Integer<uint16_t>;
    template class Integer<uint32_t>;
}
