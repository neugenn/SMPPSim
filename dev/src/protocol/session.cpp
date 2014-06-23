#include "session.h"
#include "socket.h"
#include "hostaddress.h"

#include <cassert>

namespace SMPP
{
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
        Network::HostAddress a;
        socket.GetPeerName(&a);
        return s << "New SMPP connection with " << a;
    }
}
