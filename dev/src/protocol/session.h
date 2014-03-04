#ifndef SESSION_H_
#define SESSION_H_

namespace Network
{
	class TcpSocket;
}

namespace SMPP
{
	class SmppSession
	{
		public:
			SmppSession(Network::TcpSocket*& s);
			~SmppSession();

		private:
			Network::TcpSocket* s_;
	};
}

#endif // SESSION_H_
