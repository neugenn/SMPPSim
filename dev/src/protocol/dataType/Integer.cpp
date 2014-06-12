#include "Integer.h"

namespace SMPP
{
    template <size_t T>
    Integer<T>::Integer(const unsigned char* data) : PduDataType()
    {
        if (NULL == data)
        {
            throw std::invalid_argument("NULL not allowed !");
        }

        bzero(&data_, T);
        memcpy(data_, data, T);
    }

    template <size_t T>
    Integer<T>::Integer() : PduDataType()
    {
        bzero(&data_, T);
    }

    template <size_t T>
    Integer<T>::~Integer() {}

    template <size_t T>
    const unsigned char* Integer<T>::Data() const
    {
        return data_;
    }

    template <size_t T>
    size_t Integer<T>::Size() const
    {
        return T;
    }

    template class Integer<size_t(1)>;
    template class Integer<size_t(2)>;
    template class Integer<size_t(4)>;
}
