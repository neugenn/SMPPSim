#include "session.h"
#include "socket.h"
#include "hostaddress.h"
#include "logger.h"

#include <cassert>

namespace SMPP
{
	SmppSession::SmppSession(Network::TcpSocket*& s) : s_(s)
	{
		assert(NULL != s);
		s = NULL;

		Network::HostAddress a;
		s_->GetPeerName(&a);
		FILE_LOG(logDEBUG1) << "Established a new SMPP session with " << a;
	}

	SmppSession::~SmppSession()
	{
		delete s_;
	}
}
