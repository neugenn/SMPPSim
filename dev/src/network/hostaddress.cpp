#include "hostaddress.h"
#include <arpa/inet.h>
#include <cassert>

namespace Network
{
	bool HostAddress::IsValidIp(const std::string& ip)
	{
		struct sockaddr_in s;
		int res = inet_pton(AF_INET, ip.c_str(), &s.sin_addr);
		return (1 == res);
	}

	HostAddress::HostAddress() : addr_() 
	{}

	HostAddress::HostAddress(const std::string& ip, port_t port) : addr_()
	{
		assert(HostAddress::IsValidIp(ip));
		bzero(&addr_, sizeof(addr_));

		int res = inet_pton(AF_INET, ip.c_str(), &addr_.sin_addr.s_addr); 
		assert(1 == res);
		addr_.sin_port = htons(port);
	}

	HostAddress::HostAddress(SpecialAddress address, port_t port) : addr_()
	{
		bzero(&addr_, sizeof(addr_));
		if (Any == address)
		{
			addr_.sin_addr.s_addr = htonl(INADDR_ANY);
		}
		else if (Localhost == address)
		{
			int res = inet_pton(AF_INET, "127.0.0.1", &addr_.sin_addr.s_addr); 
			assert(1 == res);
		}
		else
		{
			assert(NULL == "Unhandled SpecialAddress type!");
		}

		addr_.sin_port = htons(port);
	}

	HostAddress::~HostAddress()
	{}

	std::string HostAddress::IpToString() const
	{
		char stringRep[INET_ADDRSTRLEN];
		const char* res = inet_ntop(AF_INET, &addr_.sin_addr.s_addr, stringRep, sizeof(stringRep));
		assert(NULL != res);
		return std::string(res);
	}

	unsigned HostAddress::IpToNumeric() const
	{
		return ntohl(addr_.sin_addr.s_addr);
	}

	port_t HostAddress::Port() const
	{
		return ntohs(addr_.sin_port);
	}

	std::ostream& operator<<(std::ostream& s, const Network::HostAddress& a)
	{
		s << a.IpToString() << ":" << (unsigned short)a.Port(); 
		return s;
	}
}
