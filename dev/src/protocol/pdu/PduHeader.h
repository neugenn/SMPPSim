#ifndef PDUHEADER_H
#define PDUHEADER_H

#include "Integer.h"
#include "CommandId.h"
#include "CommandStatus.h"

class PduHeader : public PduDataType
{
public:
    static const size_t HeaderSize = 16; //bytes

    /*!
     * \brief Creates an empty PduHeader object
     */
    PduHeader();

    /*!
     * \brief Creates a PduHeader object from a stream of bytes
     * \param[in] dataBuf The data buffer
     * \throw std::invalid_argument The data buffer is NULL
     */
    PduHeader(const unsigned char*& data);

    /*!
     * \brief
     * \return
     */
    virtual const unsigned char* Data() const;

    /*!
     * \brief Size
     * \return
     */
    virtual size_t Size() const;

    /*!
     * \brief IsValid
     * \return
     */
    virtual bool IsValid() const;

    SMPP::FourByteInteger::value_t CommandLength() const;
    void SetCommandLength(SMPP::FourByteInteger::value_t len);

    SMPP::CommandId CommandId() const;
    void SetCommandId(SMPP::CommandId id);

    SMPP::CommandStatus CommandStatus() const;
    void SetCommandStatus(SMPP::CommandStatus status);

    SMPP::FourByteInteger::value_t SequenceNumber() const;
    void SetSequenceNumber(SMPP::FourByteInteger::value_t value);

    void GetFormattedContent(std::string& res) const;

private:
    SMPP::FourByteInteger commandLen_;
    SMPP::FourByteInteger commandId_;
    SMPP::FourByteInteger commandStatus_;
    SMPP::FourByteInteger sequenceNum_;
    mutable unsigned char data_[HeaderSize];
};

#endif // PDUHEADER_H
