#ifndef SOCKET_H_
#define SOCKET_H_

#include <string>

namespace Network
{
	typedef unsigned short port_t;

	class HostAddress;

	class TcpSocket
	{
		public:
			explicit TcpSocket(int descr);
			TcpSocket();
			~TcpSocket();

		public:
			bool Init();
			bool Listen(const HostAddress& a);
			bool Connect(const HostAddress& a);
			void Close();
			bool GetSockName(HostAddress* a);
			bool GetPeerName(HostAddress* a);
			int GetDescriptor() const;
			bool IsValid() const;

			ssize_t Read(
				unsigned char* buf,
			       	size_t nbytes
				);
			ssize_t Write(
				unsigned const char* buf,
				size_t nbytes
				);

			size_t ListenQueueSize() const;
			void SetListenQueueSize(size_t v);
			std::string& GetErrorMessage() const;

		private:
			TcpSocket(const TcpSocket&);
			TcpSocket& operator=(const TcpSocket&);

		protected:
			class TcpSocketImpl;
			TcpSocketImpl* impl_;
	};
}
#endif // SOCKET_H_
