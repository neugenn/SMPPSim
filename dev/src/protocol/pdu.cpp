#include "pdu.h"
#include "logger.h"
#include <arpa/inet.h>
#include <cstring>

namespace SMPP
{
	Integer::Integer(uint32_t v) : PduDataType(), data_(v), msbdata_(v)
	{}

	Integer::~Integer()
	{}

	const unsigned char* Integer::Data() const 
	{
		msbdata_ = htonl(data_);
		return reinterpret_cast<const unsigned char*>(&msbdata_);
	}

	size_t Integer::Size() const 
	{ 
		return sizeof(data_); 
	}

	COctetString COctetString::OctetString(const char* buff, size_t maxSize)
	{
		COctetString r("");
		do
		{
			if (NULL == buff)
			{
				FILE_LOG(logWARNING) << "NULL buffer used to initialize a COctetString !";
				break;
			}

			if (strlen(buff) + 1 > maxSize)
			{
				FILE_LOG(logWARNING) << "MaxSize[" << maxSize << "] buffer overflow COctetString !";
				break;
			}

			const char* it = buff;
			bool exit = false;
			while (0x00 != static_cast<unsigned int>(*it))
			{
				if ( static_cast<unsigned int>(*it) > 0x7E )
				{
					FILE_LOG(logWARNING) << "Non ASCII character (" << static_cast<int>(*it) << ") used to initialize a COctetString !";
					exit = true;
					break;
				}
				++it;
			}

			if (exit)
			{
				break;
			}

			r = COctetString(buff);
		}
		while (false);

		return r;
	}

	COctetString::~COctetString() 
	{}

	COctetString::COctetString(const char* buff) : PduDataType(), data_(buff) 
	{}

	const unsigned char* COctetString::Data() const
	{
		return reinterpret_cast<const unsigned char*>(data_.c_str());
	}

	size_t COctetString::Size() const
	{
		return data_.size() + 1;
	}

	std::ostream& operator<<(std::ostream& s, const PduDataType& dt)
	{
		s << "0x";
		const unsigned char* it = dt.Data();
		for(size_t i = 0; i < dt.Size(); ++i)
		{
			s << std::setfill('0') << std::setw(2) << std::hex << static_cast<unsigned int>(it[i]);
		}

		return s;
	}
}
