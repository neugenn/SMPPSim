#include "socket.h"
#include "hostaddress.h"
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cassert>

namespace Network
{
	struct TcpSocket::TcpSocketImpl
	{
		int fd_;
		unsigned lqs_;
		std::string error_;

		TcpSocketImpl() : fd_(-1), lqs_(100), error_() {}
		TcpSocketImpl(int d) : fd_(d), lqs_(100), error_() {}
	};

	TcpSocket::TcpSocket() : impl_(new TcpSocket::TcpSocketImpl)
	{
		this->Init();
	}

	TcpSocket::TcpSocket(int descr) : impl_(new TcpSocket::TcpSocketImpl(descr))
	{}

	TcpSocket::~TcpSocket()
	{
		if (NULL != impl_)
		{
			this->Close();
			delete impl_;
		}
	}

	bool TcpSocket::Listen(const HostAddress& a)
	{
		bool r = false;
		do
		{
			struct sockaddr_in address;
			bzero(&address, sizeof(address));

			address.sin_family = AF_INET;
			address.sin_addr.s_addr = htonl(a.IpToNumeric());
			address.sin_port = htons(a.Port());

			int res = bind(impl_->fd_, (struct sockaddr*)&address, sizeof(address));
			if (0 != res)
			{
				impl_->error_ = strerror(errno);
				break;
			}

			res = listen(impl_->fd_, impl_->lqs_);
			if (0 != res)
			{
				impl_->error_ = strerror(errno);
				break;
			}

			r = true;
		}
		while (false);

		return r;
	}

	void TcpSocket::Close()
	{
		close(impl_->fd_);
	}

	bool TcpSocket::Connect(const HostAddress& a)
	{
		bool r = false;
		do
		{
			struct sockaddr_in address;
			bzero(&address, sizeof(address));

			address.sin_family = AF_INET;
			address.sin_addr.s_addr = htonl(a.IpToNumeric());
			address.sin_port = htons(a.Port());

			int res = connect(impl_->fd_, (struct sockaddr*)&address, sizeof(address));
			if (0 != res)
			{
				break;
			}

			r = true;
		}
		while(false);

		return r;
	}

	ssize_t TcpSocket::Read(
		unsigned char* buf,
		size_t nbytes
		)
	{
		if (NULL == buf)
		{
			impl_->error_ = "Read into NULL buffer !";
			return -1;
		}

		ssize_t toRead = nbytes;
		ssize_t readBytes = 0;
		ssize_t total = 0;
		while ( readBytes < toRead )
		{	
			readBytes = read(impl_->fd_, buf, toRead);
			if (-1 == readBytes)
			{
				impl_->error_ = strerror(errno);
				total = -1;
				break;
			}

			if (0 == readBytes)
			{
				total = 0;
				break;
			}
			
			toRead -= readBytes;
			total += readBytes;
			buf += readBytes;
			readBytes = 0;
		}

		return total;
	}

	ssize_t TcpSocket::Write(
		unsigned const char* buf,
		size_t nbytes
		)
	{
		if (NULL == buf)
		{
			impl_->error_ = "Write from NULL buffer !";
			return -1;
		}

		ssize_t w = -1;
		if ( (w = write(impl_->fd_, buf, nbytes)) < 0)
		{
			std::cerr << "Error on write !" << std::endl;
			return -1;
		}

		return w;
	}

	std::string& TcpSocket::GetErrorMessage() const
	{
		return impl_->error_;
	}

	bool TcpSocket::Init() 
	{
		this->Close();

		impl_->fd_ = socket(AF_INET, SOCK_STREAM, 0);
		if (impl_->fd_ < 0)
		{
			impl_->error_ = strerror(errno);
		}

		return (impl_->fd_ > 0);
	}

	size_t TcpSocket::ListenQueueSize() const
	{
		return impl_->lqs_;
	}

	void TcpSocket::SetListenQueueSize(size_t v)
	{
		impl_->lqs_ = v;
	}

    bool TcpSocket::GetSockName(HostAddress* a) const
	{
		bool r = false;
		do
		{
			if (NULL == a)
			{
				break;
			}

			struct sockaddr_in address;
			bzero(&address, sizeof(address));

			socklen_t len = sizeof(address);

			int res = getsockname(impl_->fd_, (struct sockaddr*) &address, &len);
			if (0 != res)
			{
				impl_->error_ = strerror(errno);
				*a = HostAddress();
				break;
			}

			char stringRep[INET_ADDRSTRLEN];
			const char* ip = inet_ntop(AF_INET, &address.sin_addr.s_addr, stringRep, sizeof(stringRep));
			assert(NULL != ip);

			*a = HostAddress(stringRep, ntohs(address.sin_port));
			r = true;
		}
		while (false);

		return r;
	}

    bool TcpSocket::GetPeerName(HostAddress* a) const
	{
		bool r = false;
		do
		{
			if (NULL == a)
			{
				break;
			}

			struct sockaddr_in address;
			bzero(&address, sizeof(address));

			socklen_t len = sizeof(address);

			int res = getpeername(impl_->fd_, (struct sockaddr*) &address, &len);
			if (0 != res)
			{
				impl_->error_ = strerror(errno);
				*a = HostAddress();
				break;
			}

			char stringRep[INET_ADDRSTRLEN];
			const char* ip = inet_ntop(AF_INET, &address.sin_addr.s_addr, stringRep, sizeof(stringRep));
			assert(NULL != ip);

			*a = HostAddress(stringRep, ntohs(address.sin_port));
			r = true;
		}
		while (false);

		return r;
	}

	int TcpSocket::GetDescriptor() const
	{
		return impl_->fd_;
	}

	bool TcpSocket::IsValid() const
	{
		return (impl_->fd_ >= 0);
	}
}
