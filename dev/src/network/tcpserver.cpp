#include "tcpserver.h"
#include "hostaddress.h"
#include "socket.h"

#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>
#include <cstring>

namespace Network
{
	struct TcpServer::TcpServerImpl
	{
		TcpSocket ls_;
		fd_set rdset_;
		struct timeval tv_;

		TcpServerImpl() : ls_(), rdset_(), tv_()
		{
			FD_ZERO(&rdset_);
		}
	};

	TcpServer::TcpServer() : impl_(new TcpServer::TcpServerImpl) {}
	TcpServer::~TcpServer() 
	{
		if (NULL != impl_)
		{
			delete impl_;
		}
	}

	bool TcpServer::Listen(const HostAddress& address)
	{
		return impl_->ls_.Listen(address);
	}

	void TcpServer::Close()
	{
		impl_->ls_.Close();
	}

	bool TcpServer::WaitForNewConnection(int sec, bool* timedOut)
	{
		FD_SET(impl_->ls_.GetDescriptor(), &(impl_->rdset_));
		impl_->tv_.tv_sec = sec;

		int res = select(impl_->ls_.GetDescriptor() + 1, &(impl_->rdset_), NULL, NULL, &(impl_->tv_));

		bool r = false;
		do
		{
			if (0 == res) //timeout
			{
				if (NULL != timedOut)
				{
					*timedOut = true;
					break;
				}
			}

			if (-1 == res) //error
			{
				std::cout << strerror(errno) << std::endl;
				break;
			}

			if (FD_ISSET(impl_->ls_.GetDescriptor(), &(impl_->rdset_)))
			{
				r = true;
			}
		}
		while (false);

		return r;
	}	

	TcpSocket* TcpServer::NextPendingConnection()
	{
		TcpSocket* res = NULL;
		int client = accept(impl_->ls_.GetDescriptor(), NULL, NULL);
		if (client > 0)
		{
			res = new TcpSocket(client);
		}

		return res;
	}
}
