#ifndef PDU_H
#define PDU_H

#include "PduDataType.h"
#include "PduHeader.h"
#include <string>

class Pdu : public PduDataType
{
public:
    Pdu();
    Pdu(const Pdu& rsh);
    Pdu& operator=(const Pdu& rsh);
    virtual ~Pdu();

    const PduHeader& GetHeader() const;
    void SetSequenceNumber(uint32_t value);
    void SetCommandStatus(uint32_t status);

    /*!
     * @brief Prepares the formatted content of the PDU body
     * @param[out] s The content of the PDU body
     */
    virtual void GetBodyInfo(std::string& s) const {}

    /*!
     * @brief The minimum size of the PDU
     */
    virtual size_t MinSize() const = 0;

    /*!
     * @brief The maximum size of the PDU
     */
    virtual size_t MaxSize() const = 0;

protected:
    void SetHeader(PduHeader*& h);
    void UpdateCommandLength();

private:
    PduHeader* header_;
};

std::ostream& operator<<(std::ostream& s, const Pdu& pdu);

#endif // PDU_H
