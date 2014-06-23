#ifndef PDU_H
#define PDU_H

#include "PduDataType.h"
#include "PduHeader.h"
#include <string>
#include <vector>

class Pdu : public PduDataType
{
public:
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

    const PduHeader& GetHeader() const;
    void SetSequenceNumber(uint32_t value);
    void SetCommandStatus(uint32_t status);

    /*!
     * @brief Prepares the formatted content of the PDU body
     * @param[out] s The content of the PDU body
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

    virtual bool IsValid();

protected:
    void SetHeader(const PduHeader& h);
    void UpdateCommandLength();
    void GetBodyElements(std::vector<PduDataType*>& elements);

protected:
    PduHeader header_;
};

std::ostream& operator<<(std::ostream& s, const Pdu& pdu);

#endif // PDU_H
