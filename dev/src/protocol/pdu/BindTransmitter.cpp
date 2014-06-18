#include "BindTransmitter.h"

namespace SMPP
{
    const size_t BindTransmitter::SystemIdMaxLen = 16; //bytes
    const size_t BindTransmitter::PasswordMaxLen = 9; //bytes
    const size_t BindTransmitter::SystemTypeMaxLen = 13; //bytes
    const size_t BindTransmitter::AddressRangeMaxLen = 41; //bytes

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
        PduHeader* ph = new PduHeader();
        ph->SetCommandId(0x00000002);
        this->SetHeader(ph);
    }

    BindTransmitter::BindTransmitter(const unsigned char* data, size_t len) :
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
        PduHeader* ph = NULL;
        try
        {
            ph = new PduHeader(data);
            this->SetHeader(ph);
            this->initBody(data, len);
            if (0x00000002 != this->GetHeader().GetCommandId())
            {
                throw std::invalid_argument("BindTransmitter() : invalid command id !");
            }
        }
        catch (std::exception& e)
        {
            if (NULL != ph)
            {
                delete ph;
            }
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

    BindTransmitter::BindTransmitter(PduHeader*& rsh) : Pdu(),
    systemId_("system_id"),
    password_("password"),
    systemType_("system_type"),
    interfaceVersion_("interface_version"),
    addrTon_("addr_ton"),
    addrNpi_("addr_npi"),
    addressRange_("address_range"),
    data_(NULL)
    {
        rsh->SetCommandId(0x00000002);
        this->SetHeader(rsh);
    }

    BindTransmitter::BindTransmitter(const BindTransmitter &rsh) :
    Pdu(rsh),
    systemId_(rsh.systemId_),
    password_ (rsh.password_),
    systemType_ (rsh.systemType_),
    interfaceVersion_(rsh.interfaceVersion_),
    addrTon_(rsh.addrTon_),
    addrNpi_(rsh.addrNpi_),
    addressRange_(rsh.addressRange_),
    data_(NULL)
    {
    }

    BindTransmitter& BindTransmitter::operator =(const BindTransmitter &rsh)
    {
        if (this == &rsh)
        {
            return *this;
        }

        Pdu::operator=(rsh);
        systemId_ = rsh.systemId_;
        password_ = rsh.password_;
        systemType_ = rsh.systemType_;
        interfaceVersion_ = rsh.interfaceVersion_;
        addrTon_ = rsh.addrTon_;
        addrNpi_ = rsh.addrNpi_;
        addressRange_ = rsh.addressRange_;

        return *this;
    }

    void BindTransmitter::initBody(const unsigned char *data, size_t len)
    {
       size_t offset = GetHeader().Size();
       systemId_ = CString(data + offset, SystemIdMaxLen, "system_id");

       offset += systemId_.Size();
       password_ = CString(data + offset, PasswordMaxLen, "password");

       offset += password_.Size();
       systemType_ = CString(data + offset, SystemTypeMaxLen, "system_type");

       offset += systemType_.Size();
       interfaceVersion_ = OneByteInteger(data + offset, "interface_version");

       offset += interfaceVersion_.Size();
       addrTon_ = OneByteInteger(data + offset, "addr_ton");

       offset += addrTon_.Size();
       addrNpi_ = OneByteInteger(data + offset, "addr_npi");

       offset += addrNpi_.Size();
       addressRange_ = CString(data + offset, AddressRangeMaxLen, "address_range");

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
