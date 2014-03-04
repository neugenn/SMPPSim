#include "server.h"
#include "hostaddress.h"
#include "logger.h"
#include "pdu.h"
#include "sdk/timer/timer.h"
#include <unistd.h>

int main(int argc, char* argv[])
{
	Logger::Init();

	/*
	Network::HostAddress address(Network::HostAddress::Any, 8129);
	FILE_LOG(logINFO) << "Starting server on address : " << address;
	FILE_LOG(logDEBUG) << "Cool !";

	Network::Server server;
	server.Start(address);

	const char buf[] = { 0x31, 0x61, 0x18, 0x00 };
	SMPP::COctetString cs = SMPP::COctetString::OctetString(buf, sizeof(buf));
	FILE_LOG(logDEBUG) << cs;

	SMPP::Integer in(3012);
	FILE_LOG(logDEBUG) << in;
	*/

	SDK::Timer t(10);
	t.Start();

	for (;;)
	{
		sleep(10);
	}
	Logger::Release();

	return 0;
}
