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
    PduHeader& GetHeader();
    void SetHeader(PduHeader*& h);

    /*!
     * @brief Prepares the formatted content of the PDU body
     * @param[out] s The content of the PDU body
     */
    virtual void GetBodyInfo(std::string& s) const = 0;

private:
    PduHeader* header_;
};

std::ostream& operator<<(std::ostream& s, const Pdu& pdu);

#endif // PDU_H
