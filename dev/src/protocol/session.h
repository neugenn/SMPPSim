#ifndef SESSION_H_
#define SESSION_H_
#include <ostream>

namespace Network
{
	class TcpSocket;
}

namespace SMPP
{
    class Session
	{
		public:
            Session(Network::TcpSocket*& s);
            ~Session();
            const Network::TcpSocket& Socket() const;

		private:
			Network::TcpSocket* s_;
    };

    std::ostream& operator<<(std::ostream& s, const Session& session);

    Session::Session(Network::TcpSocket*& s) : s_(s)
    {
        assert(NULL != s);
        s = NULL;
    }

    const Network::TcpSocket& Session::Socket() const
    {
        return *s_;
    }

    Session::~Session()
    {
        delete s_;
    }

    std::ostream& operator<<(std::ostream& s, const Session& session)
    {
        const Network::TcpSocket& socket = session.Socket();
        Network::HostAddress from;
        socket.GetPeerName(&from);

        Network::HostAddress to;
        socket.GetSockName(&to);
        return s << "New connection from " << from << " to " << to;
    }
}

#endif // SESSION_H_
