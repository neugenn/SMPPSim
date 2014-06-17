#include "BindTransmitter.h"

namespace SMPP
{
    BindTransmitter::BindTransmitter() :
    Pdu(),
    systemId_("system_id"),
    password_("password"),
    systemType_("system_type"),
    interfaceVersion_("interface_version"),
    addrTon_("addr_ton"),
    addrNpi_("addr_npi"),
    addressRange_("address_range"),
    data_(NULL)
    {
        header_.SetCommandId(0x00000002);
    }

    BindTransmitter::BindTransmitter(const unsigned char* data, size_t len) :
    Pdu(data),
    systemId_("system_id"),
    password_("password"),
    systemType_("system_type"),
    interfaceVersion_("interface_version"),
    addrTon_("addr_ton"),
    addrNpi_("addr_npi"),
    addressRange_("address_range"),
    data_(NULL)
    {
        if (0x00000002 != header_.GetCommandId())
        {
            throw std::invalid_argument("BindTransmitter() : invalid command id !");
        }

        try
        {
            this->initBody(data, len);
        }
        catch (std::exception& e)
        {
            throw;
        }
    }

    BindTransmitter::~BindTransmitter()
    {
        if (NULL != data_)
        {
            delete [] data_;
        }
    }

    BindTransmitter::BindTransmitter(const BindTransmitter &lsh) :
    Pdu(lsh.header_),
    systemId_(lsh.systemId_),
    password_ (lsh.password_),
    systemType_ (lsh.systemType_),
    interfaceVersion_(lsh.interfaceVersion_),
    addrTon_(lsh.addrTon_),
    addrNpi_(lsh.addrNpi_),
    addressRange_(lsh.addressRange_),
    data_(NULL)
    {
    }

    void BindTransmitter::initBody(const unsigned char *data, size_t len)
    {
       size_t offset = GetHeader().Size();
       systemId_ = CString(data + offset, SystemIdLen, "system_id");

       offset += systemId_.Size();
       password_ = CString(data + offset, PasswordLen, "password");

       offset += password_.Size();
       systemType_ = CString(data + offset, SystemTypeLen, "system_type");

       offset += systemType_.Size();
       interfaceVersion_ = OneByteInteger(data + offset, "interface_version");

       offset += interfaceVersion_.Size();
       addrTon_ = OneByteInteger(data + offset, "addr_ton");

       offset += addrTon_.Size();
       addrNpi_ = OneByteInteger(data + offset, "addr_npi");

       offset += addrNpi_.Size();
       addressRange_ = CString(data + offset, AddressRangeLen, "address_range");

       offset += addressRange_.Size();
       if (offset != len)
       {
//           throw std::invalid_argument("FOO");
       }
    }

    void BindTransmitter::GetBodyInfo(std::string &s) const
    {
        std::stringstream str;
        str << "system_id: " << systemId_ << " (" << systemId_.Value() << ")" << std::endl;
        str << "password: " << password_ << " (" << password_.Value() << ")" << std::endl;
        str << "system_type: " << systemType_ << " (" << systemType_.Value() << ")" << std::endl;
        str << "interface_version: " << interfaceVersion_ << std::endl;
        str << "addr_ton: " << addrTon_ << std::endl;
        str << "addr_npi: " << addrNpi_ << std::endl;
        str << "address_range: " << addressRange_;

        s = str.str();
    }

    unsigned const char* BindTransmitter::Data() const
    {
        const size_t size = this->Size();
        if (NULL != data_)
        {
            delete [] data_;
        }

        unsigned char* buf = new unsigned char[size];
        const PduHeader& h = GetHeader();

        size_t offset  = 0;
        memcpy(buf, h.Data(), h.Size());
        offset += h.Size();

        memcpy(buf + offset, systemId_.Data(), systemId_.Size());
        offset += h.Size();

        data_ = buf;
        return data_;
    }

    size_t BindTransmitter::Size() const
    {
        const size_t size = GetHeader().Size() + systemId_.Size() + password_.Size() + systemType_.Size() \
                + interfaceVersion_.Size() + addrTon_.Size() + addrNpi_.Size() + addressRange_.Size();

        return size;
    }
}
