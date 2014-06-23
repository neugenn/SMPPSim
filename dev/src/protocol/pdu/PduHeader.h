#ifndef PDUHEADER_H
#define PDUHEADER_H

#include "Integer.h"

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
    PduHeader(const unsigned char* dataBuf);

    virtual const unsigned char* Data() const;
    virtual size_t Size() const;
    virtual bool IsValid();

    uint32_t GetCommandLength() const;
    void SetCommandLength(uint32_t len);

    uint32_t GetCommandId() const;
    void SetCommandId(uint32_t len);

    const SMPP::FourByteInteger& GetCommandStatus() const;
    void SetCommandStatus(uint32_t status);

    uint32_t GetSequenceNumber() const;
    void SetSequenceNumber(uint32_t value);

    void GetFormattedContent(std::string& res) const;

private:
    void init(const unsigned char* data);

private:
    SMPP::FourByteInteger commandLen_;
    SMPP::FourByteInteger commandId_;
    SMPP::FourByteInteger commandStatus_;
    SMPP::FourByteInteger sequenceNum_;
    mutable unsigned char data_[HeaderSize];
};

#endif // PDUHEADER_H
