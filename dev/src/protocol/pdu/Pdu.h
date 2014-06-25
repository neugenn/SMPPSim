#ifndef PDU_H
#define PDU_H

#include "PduDataType.h"
#include "PduHeader.h"
#include <string>
#include <vector>

class Pdu : public PduDataType
{
public:
    static SMPP::FourByteInteger::value_t MaxSequenceNumber();

    /*!
     * \brief Creates an empty Pdu object
     */
    Pdu();

    /*!
     * \brief Creates a Pdu object from a stream of bytes
     * \param data
     * \throw std::invalid_argument The data buffer is NULL
     */
    Pdu(const unsigned char* data);
    virtual ~Pdu();

    SMPP::FourByteInteger::value_t CommandLength() const;
    SMPP::CommandId CommandId() const;

    SMPP::CommandStatus CommandStatus() const;
    void SetCommandStatus(SMPP::CommandStatus status);

    SMPP::FourByteInteger::value_t SequenceNumber() const;

    /*!
     * \brief SetSequenceNumber
     * \param value
     * \throw std::invalid_argument The value exeeds the maximum allowed value
     */
    void SetSequenceNumber(SMPP::FourByteInteger::value_t value);

    /*!
     * @brief Prepares the formatted content of the PDU
     * @param[out] s The content of the PDU
     */
    virtual void GetFormattedContent(std::string& s) const;

    /*!
     * @brief The minimum size of the PDU
     */
    virtual size_t MinSize() const = 0;

    /*!
     * @brief The maximum size of the PDU
     */
    virtual size_t MaxSize() const = 0;

    virtual bool IsValid() const;

protected:
    void SetHeader(const PduHeader& h);
    void UpdateCommandLength();

private:
    virtual void GetBodyElements(std::vector<const PduDataType*>& elements) const;
    bool IsValidBody() const;

protected:
    PduHeader header_;
};

std::ostream& operator<<(std::ostream& s, const Pdu& pdu);

#endif // PDU_H
