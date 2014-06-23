#include "BindTransmitter.h"

namespace SMPP
{
    const size_t BindTransmitter::SystemIdMaxLen = 16; //bytes
    const size_t BindTransmitter::PasswordMaxLen = 9; //bytes
    const size_t BindTransmitter::SystemTypeMaxLen = 13; //bytes
    const size_t BindTransmitter::AddressRangeMaxLen = 41; //bytes

    static const size_t MIN_SIZE = PduHeader::HeaderSize + 4 * CString().Size() + 3 * OneByteInteger().Size();
    static const size_t MAX_SIZE = PduHeader::HeaderSize + BindTransmitter::SystemIdMaxLen + BindTransmitter::PasswordMaxLen + \
            BindTransmitter::SystemTypeMaxLen + BindTransmitter::AddressRangeMaxLen + 3 * OneByteInteger().Size();

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
        header_.SetCommandLength(MIN_SIZE);
    }

    BindTransmitter::BindTransmitter(const unsigned char* data) :
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
        const uint32_t commandLen = header_.GetCommandLength();
        try
        {
            this->initBody(data);
            if (0x00000002 != header_.GetCommandId())
            {
                std::stringstream s;
                s << __PRETTY_FUNCTION__;
                s << " : invalid command_id(" << std::hex << GetHeader().GetCommandId();
                throw std::invalid_argument(s.str());
            }
        }
        catch (std::exception& e)
        {
            std::stringstream s;
            s << __PRETTY_FUNCTION__ << std::endl << e.what();
            throw std::invalid_argument(s.str());
        }

        if (commandLen < MIN_SIZE)
        {
            std::stringstream s;
            s << __PRETTY_FUNCTION__ << " : command_length(" << commandLen;
            s << ") smaller than minimum allowed PDU length(" << MIN_SIZE <<") !";
            throw std::invalid_argument(s.str());
        }

        if (commandLen > MAX_SIZE)
        {
            std::stringstream s;
            s << __PRETTY_FUNCTION__ << " : command_length(" << commandLen;
            s << ") greater than maximum allowed PDU length(" << MAX_SIZE <<") !";
            throw std::invalid_argument(s.str());
        }
    }

    BindTransmitter::~BindTransmitter()
    {
        if (NULL != data_)
        {
            delete [] data_;
        }
    }

    BindTransmitter::BindTransmitter(const PduHeader& rsh) : Pdu(),
    systemId_("system_id"),
    password_("password"),
    systemType_("system_type"),
    interfaceVersion_("interface_version"),
    addrTon_("addr_ton"),
    addrNpi_("addr_npi"),
    addressRange_("address_range"),
    data_(NULL)
    {
        this->SetHeader(rsh);
        header_.SetCommandLength(MIN_SIZE);
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

    void BindTransmitter::initBody(const unsigned char *data)
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
    }

    void BindTransmitter::GetFormattedContent(std::string &s) const
    {
        s.clear();
        Pdu::GetFormattedContent(s);

        std::stringstream str;
        str << s;
        str << "system_id: " << systemId_ << " (" << systemId_.Value() << ")" << std::endl;
        str << "password: " << password_ << " (" << password_.Value() << ")" << std::endl;
        str << "system_type: " << systemType_ << " (" << systemType_.Value() << ")" << std::endl;
        str << "interface_version: " << interfaceVersion_ << std::endl;
        str << "addr_ton: " << addrTon_ << std::endl;
        str << "addr_npi: " << addrNpi_ << std::endl;
        str << "address_range: " << addressRange_;

        s = str.str();
    }

    size_t BindTransmitter::MinSize() const
    {
        return MIN_SIZE;
    }

    size_t BindTransmitter::MaxSize() const
    {
        return MAX_SIZE;
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

        memcpy(buf, h.Data(), h.Size());
        size_t offset = h.Size();

        memcpy(buf + offset, systemId_.Data(), systemId_.Size());
        offset += systemId_.Size();

        memcpy(buf + offset, password_.Data(), password_.Size());
        offset += password_.Size();

        memcpy(buf + offset, systemType_.Data(), systemType_.Size());
        offset += systemType_.Size();

        memcpy(buf + offset, interfaceVersion_.Data(), interfaceVersion_.Size());
        offset += interfaceVersion_.Size();

        memcpy(buf + offset, addrTon_.Data(), addrTon_.Size());
        offset += addrTon_.Size();

        memcpy(buf + offset, addrNpi_.Data(), addrNpi_.Size());
        offset += addrNpi_.Size();

        memcpy(buf + offset, addressRange_.Data(), addressRange_.Size());
        offset += addressRange_.Size();

        data_ = buf;
        return data_;
    }

    size_t BindTransmitter::Size() const
    {
        const size_t size = GetHeader().Size() + systemId_.Size() + password_.Size() + systemType_.Size() \
                + interfaceVersion_.Size() + addrTon_.Size() + addrNpi_.Size() + addressRange_.Size();

        return size;
    }

    void BindTransmitter::GetBodyElements(std::vector<PduDataType *> &elements)
    {
        elements.clear();
        elements.push_back(&systemId_);
        elements.push_back(&password_);
        elements.push_back(&systemType_);
        elements.push_back(&interfaceVersion_);
        elements.push_back(&addrTon_);
        elements.push_back(&addrNpi_);
        elements.push_back(&addressRange_);
    }
}
