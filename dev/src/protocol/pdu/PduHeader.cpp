#include "PduHeader.h"

namespace SMPP
{
    PduHeader::PduHeader(const unsigned char* dataBuf) :
    PduDataType(),
    commandLen_(),
    commandId_(),
    commandStatus_(),
    sequenceNum_(),
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

    const SMPP::FourByteInteger& PduHeader::CommandLength() const
    {
        return commandLen_;
    }

    const SMPP::FourByteInteger& PduHeader::CommandId() const
    {
        return commandId_;
    }

    const SMPP::FourByteInteger& PduHeader::CommandStatus() const
    {
        return commandStatus_;
    }

    const SMPP::FourByteInteger& PduHeader::SequenceNumber() const
    {
        return sequenceNum_;
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

    std::ostream& operator<<(std::ostream& s, const PduHeader& data)
    {
        s << "command_length : \t" << "0x" << data.CommandLength() << std::endl;
        s << "command_id : \t" <<  "0x" << data.CommandId() << std::endl;
        s << "command_status : \t" << "0x" << data.CommandStatus() << std::endl;
        s << "sequence_number : \t" << "0x" << data.SequenceNumber() << std::endl;

        return s;
    }
}
