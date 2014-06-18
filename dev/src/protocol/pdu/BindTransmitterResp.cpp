#include "BindTransmitterResp.h"

namespace SMPP
{
    BindTransmitterResp::BindTransmitterResp() : Pdu(),
    systemId_("system_id")
    {
        PduHeader* h = new PduHeader;
        h->SetCommandId(0x80000002);
        this->SetHeader(h);
    }

    BindTransmitterResp::BindTransmitterResp(const unsigned char* data, size_t len) :
    Pdu(),
    systemId_()
    {
        PduHeader* h = new PduHeader(data);
        h->SetCommandId(0x80000002);
        this->SetHeader(h);
        systemId_ = CString(data, len, "system_id");
    }

    BindTransmitterResp::~BindTransmitterResp()
    {}

    void BindTransmitterResp::GetBodyInfo(std::string &s) const
    {
        std::stringstream str;
        str << "system_id: " << systemId_ << " (" << systemId_.Value() << ")" << std::endl;
        s = str.str();
    }

    const unsigned char* BindTransmitterResp::Data() const
    {
        const size_t size = Size();
        unsigned char* data = new unsigned char[size];

        memcpy(data, GetHeader().Data(), GetHeader().Size());
        memcpy(data + GetHeader().Size(), systemId_.Data(), systemId_.Size());

        return data;
    }

    size_t BindTransmitterResp::Size() const
    {
        const size_t size = GetHeader().Size() + systemId_.Size();
        return size;
    }

    void BindTransmitterResp::SetSystemId(const std::string &id)
    {
        std::string s(id);
        if (s.size() > SystemIdLen)
        {
            s = std::string(id.c_str(), SystemIdLen);
        }

        systemId_.SetValue(s);
        this->UpdateCommandLen();
    }

    void BindTransmitterResp::UpdateCommandLen()
    {
        this->GetHeader().SetCommandLength(this->Size());
    }
}
