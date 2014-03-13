#include "server.h"
#include "hostaddress.h"
#include "logger.h"
#include "pdu.h"
#include "sdk/timer/timer.h"
#include <unistd.h>

class Foo : public SDK::TimerCallback
{
	public:
		Foo(const char* pc) : TimerCallback(), s_(pc) {}
		~Foo() {}
	public:
		virtual void Elapsed()
		{
			std::cout << s_ << std::endl;
		}

	private:
		const std::string s_;
};

int main(int argc, char* argv[])
{
	//Logger::Init();

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

	Foo f2("World !");
	SDK::Timer t2(&f2);
	t2.Start(6);
	t2.SetSingleShot();

	{
		Foo f1("Hello ");
		SDK::Timer t1(&f1);
		t1.Start(4);
		sleep(5);
	}


	for (;;)
	{
		sleep(2);
	}
	//Logger::Release();

	return 0;
}
