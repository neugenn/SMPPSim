#ifndef PDUDATATYPE_H_
#define PDUDATATYPE_H_

#include <string>
#include <ostream>

namespace SMPP
{
    /*!
     * @brief Base class for all SMPP PDU data types
     */
    class PduDataType
    {
    public:
        PduDataType() {}
        virtual ~PduDataType() {}

        /*!
         * @brief Access to the underlying storage of the data type
         */
        virtual const unsigned char* Data() const = 0;

        /*!
         * @brief The size of the underlying storage buffer
         */
        virtual size_t Size() const = 0;

        /*!
         * @brief
         * @param[out] s
         */
        static void GetFormattedData(const unsigned char* data, size_t len, std::string& out);
    };

    std::ostream& operator<<(std::ostream& s, const PduDataType& data);
}
#endif // PDUDATATYPE_H_
