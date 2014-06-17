#include "server.h"
#include "hostaddress.h"
#include "logger.h"
#include <unistd.h>

int main(int argc, char* argv[])
{
    Logger::Init();

//	/*
	Network::HostAddress address(Network::HostAddress::Any, 8129);
	FILE_LOG(logINFO) << "Starting server on address : " << address;
	FILE_LOG(logDEBUG) << "Cool !";

	Network::Server server;
	server.Start(address);

//	*/

	for (;;)
	{
		sleep(2);
	}
    Logger::Release();

	return 0;
}
