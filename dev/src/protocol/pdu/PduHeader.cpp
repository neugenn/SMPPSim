#include "PduHeader.h"

PduHeader::PduHeader() : PduDataType(),
commandLen_("command_len"),
commandId_("command_id"),
commandStatus_("command_status"),
sequenceNum_("sequence_number"),
data_()
{
    bzero(&data_[0], HeaderSize);
}

PduHeader::PduHeader(const unsigned char* dataBuf) :
PduDataType(),
commandLen_("command_len"),
commandId_("command_id"),
commandStatus_("command_status"),
sequenceNum_("sequence_number"),
data_()
{
    try
    {
        this->init(dataBuf);
    }
    catch (std::exception& e)
    {
        throw;
    }

    bzero(&data_[0], HeaderSize);
}

void PduHeader::init(const unsigned char *data)
{
    commandLen_ = SMPP::FourByteInteger(data);
    data += commandLen_.Size();

    commandId_ = SMPP::FourByteInteger(data);
    data += commandId_.Size();

    commandStatus_ = SMPP::FourByteInteger(data);
    data += commandStatus_.Size();

    sequenceNum_ = SMPP::FourByteInteger(data);
}

uint32_t PduHeader::GetCommandLength() const
{
    return commandLen_.Value();
}

void PduHeader::SetCommandLength(uint32_t len)
{
    commandLen_.SetValue(len);
}

uint32_t PduHeader::GetCommandId() const
{
    return commandId_.Value();
}

void PduHeader::SetCommandId(uint32_t value)
{
    commandId_.SetValue(value);
}

const SMPP::FourByteInteger& PduHeader::GetCommandStatus() const
{
    return commandStatus_;
}

void PduHeader::SetCommandStatus(uint32_t status)
{
    commandStatus_.SetValue(status);
}

uint32_t PduHeader::GetSequenceNumber() const
{
    return sequenceNum_.Value();
}

void PduHeader::SetSequenceNumber(uint32_t val)
{
    sequenceNum_.SetValue(val);
}

void PduHeader::GetFormattedContent(std::string &res) const
{
    std::stringstream s;
    s << "command_len: 0x" << commandLen_ << " (" << commandLen_.Value() << ")" << std::endl;
    s << "command_id: 0x" << commandId_ << std::endl;
    s << "command_status: 0x" << commandStatus_ << std::endl;
    s << "sequence_number: 0x" << sequenceNum_ << " (" << sequenceNum_.Value() << ")" << std::endl;
    s << std::endl;

    res = s.str();
}

const unsigned char* PduHeader::Data() const
{
    bzero(&data_[0], this->Size());

    memcpy(data_, commandLen_.Data(), commandLen_.Size());
    size_t offset = commandLen_.Size();

    memcpy(data_ + offset, commandId_.Data(), commandId_.Size());
    offset += commandId_.Size();

    memcpy(data_ + offset, commandStatus_.Data(), commandStatus_.Size());
    offset += commandStatus_.Size();

    memcpy(data_ + offset, sequenceNum_.Data(), sequenceNum_.Size());
    return &data_[0];
}

size_t PduHeader::Size() const
{
    return PduHeader::HeaderSize;
}

bool PduHeader::IsValid()
{
    return ( commandLen_.IsValid() && commandId_.IsValid() && commandStatus_.IsValid() && sequenceNum_.IsValid() );
}
