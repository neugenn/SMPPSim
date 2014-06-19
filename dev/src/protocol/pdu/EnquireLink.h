#ifndef ENQUIRELINK_H
#define ENQUIRELINK_H

#include "Pdu.h"

namespace SMPP
{
    class EnquireLink : public Pdu
    {
    public:
        EnquireLink(const unsigned char* data);

        virtual const unsigned char* Data() const;
        virtual size_t Size() const;

        virtual size_t MinSize() const;
        virtual size_t MaxSize() const;
    };
}

#endif // ENQUIRELINK_H
