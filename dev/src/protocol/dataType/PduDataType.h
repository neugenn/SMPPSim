#ifndef PDUDATATYPE_H_
#define PDUDATATYPE_H_

#include <string>
#include <ostream>
#include <sstream>
#include <cstring>

/*!
 * @brief Base class for all PDU data types
 */
class PduDataType
{
public:
    PduDataType();
    PduDataType(const char* name);
    virtual ~PduDataType() {}

    /*!
     * @brief Name
     * @return
     */
    const std::string& Name() const;

    /*!
     * @brief Access to the underlying storage of the data type
     */
    virtual const unsigned char* Data() const = 0;

    /*!
     * @brief The size of the underlying storage buffer
     */
    virtual size_t Size() const = 0;

    virtual bool IsValid() = 0;

private:
    std::string name_;
};

std::ostream& operator<<(std::ostream& s, const PduDataType& data);
bool operator==(const PduDataType& lsh, const PduDataType& rsh);
bool operator!=(const PduDataType& lsh, const PduDataType& rsh);

#endif // PDUDATATYPE_H_
