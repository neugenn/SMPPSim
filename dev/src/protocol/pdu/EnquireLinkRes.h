#ifndef ENQUIRELINKRES_H
#define ENQUIRELINKRES_H

#include "Pdu.h"

namespace SMPP
{
    class EnquireLinkRes : public Pdu
    {
    public:
        EnquireLinkRes(const unsigned char* data);

        virtual const unsigned char* Data() const;
        virtual size_t Size() const;

        virtual size_t MinSize() const;
        virtual size_t MaxSize() const;
    };
}

#endif // ENQUIRELINK_H
