#ifndef PDU_H_
#define PDU_H_

#include "pdutype.h"

#include <stdint.h>
#include <iostream>
#include <iomanip>
#include <string>

namespace SMPP
{
	class PduDataType
	{
		public:
			PduDataType() {}
			virtual ~PduDataType() {}

		public:
			virtual const unsigned char* Data() const = 0;
			virtual size_t Size() const = 0;
	};

	class Integer : public PduDataType
	{
		public:
			explicit Integer(uint32_t v);
			~Integer();

		public:
			virtual const unsigned char* Data() const;
			virtual size_t Size() const;

		private:
			uint32_t data_;
			mutable uint32_t msbdata_;
	};

	class COctetString : public PduDataType
	{
		public:
			static COctetString OctetString(const char* buff, size_t maxSize);
			~COctetString();

		private:
			COctetString(const char* buff);

		public:
			virtual const unsigned char* Data() const;
			virtual size_t Size() const;

		private:
			std::string data_;
	};

	std::ostream& operator<<(std::ostream& s, const PduDataType& dt);

	struct Header
	{
		Integer len_;
		Integer id_;
		Integer status_;
		Integer seq_;
	};

	class Pdu
	{
		public:
			Pdu(unsigned char* data, size_t len);
			virtual ~Pdu();

		public:
			const Header& GetHeader() const;
			virtual SMPP::PduType ResponseType() const = 0;

		private:
			const Header h_;
	};
}
#endif // PDU_H_


