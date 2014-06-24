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

PduHeader::PduHeader(const unsigned char*& data) :
PduDataType(),
commandLen_(data, "command_len"),
commandId_(data, "command_id"),
commandStatus_(data, "command_status"),
sequenceNum_(data, "sequence_number"),
data_()
{
    if (NULL == data)
    {
        throw std::invalid_argument("");
    }
    bzero(&data_[0], HeaderSize);
}

SMPP::FourByteInteger::value_t PduHeader::CommandLength() const
{
    return commandLen_.Value();
}

void PduHeader::SetCommandLength(SMPP::FourByteInteger::value_t len)
{
    commandLen_.SetValue(len);
}

SMPP::CommandId PduHeader::CommandId() const
{
    return SMPP::CommandId(commandId_.Value());
}

void PduHeader::SetCommandId(SMPP::CommandId id)
{
    commandId_.SetValue(id);
}

SMPP::CommandStatus PduHeader::CommandStatus() const
{
    return SMPP::CommandStatus(commandStatus_.Value());
}

void PduHeader::SetCommandStatus(SMPP::CommandStatus status)
{
    commandStatus_.SetValue(status);
}

SMPP::FourByteInteger::value_t PduHeader::SequenceNumber() const
{
    return sequenceNum_.Value();
}

void PduHeader::SetSequenceNumber(SMPP::FourByteInteger::value_t val)
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

bool PduHeader::IsValid() const
{
    return ( commandLen_.IsValid() && commandId_.IsValid() && commandStatus_.IsValid() && sequenceNum_.IsValid() );
}
