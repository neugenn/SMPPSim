#ifndef VALIDATION_H
#define VALIDATION_H

#include <cstddef>

namespace SMPP
{
    /*!
     * @brief The interface of the validation algorithm used by a COctetString
     */
    class Validation
    {
    public:
        Validation() {}
        virtual ~Validation() {}

    public:
        virtual bool IsValid(const unsigned char* data, size_t size) = 0;
    };
}

#endif // VALIDATION_H
