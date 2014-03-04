#ifndef HOST_ADDRESS_H_
#define HOST_ADDRESS_H_

#include <netinet/in.h>
#include <cstring>
#include <iostream>

namespace Network
{
	typedef unsigned short port_t;

	class HostAddress
	{
		public:
			static bool IsValidIp(const std::string& ip);

			enum SpecialAddress
			{
				Localhost,
				Any
			};

		public:
			HostAddress();
			HostAddress(const std::string& ip, port_t port);
			HostAddress(SpecialAddress address, port_t port);
			~HostAddress();

		public:
			std::string IpToString() const;
			unsigned IpToNumeric() const;
			port_t Port() const;

		private:
			sockaddr_in addr_;
	};

	std::ostream& operator<<(std::ostream& s, const Network::HostAddress& a);
}

#endif // HOST_ADDRESS_H_
