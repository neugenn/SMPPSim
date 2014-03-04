#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

namespace Network
{
	class HostAddress;
	class TcpSocket;

	class TcpServer
	{
		public:
			TcpServer();
			~TcpServer();

			bool Listen(const HostAddress& address);
			void Close();

			bool WaitForNewConnection(int sec, bool* timedOut);
			TcpSocket* NextPendingConnection();

		private:
			TcpServer(const TcpServer&);
			TcpServer& operator=(const TcpServer&);

		private:
			class TcpServerImpl;
			TcpServerImpl* impl_;
	};
}
#endif // TCP_SERVER_H_
