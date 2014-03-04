#ifndef SERVER_H_
#define SERVER_H_

namespace Network
{
	class ServerThread;
	class HostAddress;

	class Server
	{
		public:
			Server();
			~Server();

			bool Start(const Network::HostAddress& address);
			void Stop();
			bool IsRunning() const;

		private:
			Server(const Server&);
			Server& operator=(const Server&);

		private:
			ServerThread* s_;
	};
}

#endif // SERVER_H_
