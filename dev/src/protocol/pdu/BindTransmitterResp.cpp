#include "BindTransmitterResp.h"

namespace SMPP
{
    const size_t BindTransmitterResp::SystemIdMaxLen = 16; //bytes
    const size_t MIN_SIZE = PduHeader().Size() + CString().Size();

    BindTransmitterResp::BindTransmitterResp() :
    Pdu(),
    systemId_("system_id"),
    data_(NULL)
    {
        header_.SetCommandId(0x80000002);
        header_.SetCommandLength(MIN_SIZE);
    }

    BindTransmitterResp::BindTransmitterResp(const unsigned char* data) :
    Pdu(data),
    systemId_("system_id"),
    data_(NULL)
    {
        try
        {
            header_.SetCommandLength(this->MinSize());
            systemId_ = CString(data + this->GetHeader().Size(), SystemIdMaxLen, "system_id");
        }
        catch (std::exception& e)
        {
            std::stringstream s;
            s << __PRETTY_FUNCTION__ << " " << e.what();
            throw std::invalid_argument(s.str());
        }
    }

    BindTransmitterResp::BindTransmitterResp(const BindTransmitterResp& rsh) :
    Pdu(rsh),
    systemId_(rsh.systemId_),
    data_(NULL)
    {
    }

    BindTransmitterResp& BindTransmitterResp::operator=(const BindTransmitterResp& rsh)
    {
        if (this == &rsh)
        {
            return *this;
        }

        Pdu::operator =(rsh);
        systemId_ = rsh.systemId_;
        data_ = NULL;

        return *this;
    }

    BindTransmitterResp::~BindTransmitterResp()
    {
       if (NULL != data_)
       {
           delete [] data_;
       }
    }

    void BindTransmitterResp::GetFormattedContent(std::string &s) const
    {
        s.clear();
        Pdu::GetFormattedContent(s);
        std::stringstream str;
        str << s;
        str << "system_id: " << systemId_ << " (" << systemId_.Value() << ")" << std::endl;
        s = str.str();
    }

    size_t BindTransmitterResp::MinSize() const
    {
        return MIN_SIZE;
    }

    size_t BindTransmitterResp::MaxSize() const
    {
        return this->GetHeader().Size() + SystemIdMaxLen;
    }

    const unsigned char* BindTransmitterResp::Data() const
    {
        if (NULL != data_)
        {
            delete [] data_;
        }

        const size_t size = Size();
        unsigned char* buf = new unsigned char[size];

        memcpy(buf, GetHeader().Data(), GetHeader().Size());
        memcpy(buf + GetHeader().Size(), systemId_.Data(), systemId_.Size());

        data_ = buf;
        return data_;
    }

    size_t BindTransmitterResp::Size() const
    {
        const size_t size = GetHeader().Size() + systemId_.Size();
        return size;
    }

    void BindTransmitterResp::SetSystemId(const std::string &id)
    {
        std::string s(id);
        if (s.size() > SystemIdMaxLen)
        {
            s = std::string(id.c_str(), SystemIdMaxLen);
        }

        systemId_.SetValue(s);
        this->UpdateCommandLength();
    }

    const std::string& BindTransmitterResp::GetSystemId() const
    {
        return systemId_.Value();
    }

    void BindTransmitterResp::GetBodyElements(std::vector<PduDataType *> &elements)
    {
        elements.clear();
        elements.push_back(&systemId_);
    }
}
