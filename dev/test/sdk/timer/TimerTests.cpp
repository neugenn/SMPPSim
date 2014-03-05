#include "TimerTests.h"
#include "timer.h"

//CPPUNIT_TEST_SUITE_REGISTRATION(TimerTests);

void TimerTests::setUp()
{
	timer_ = new SDK::Timer(10);
}

void TimerTests::tearDown()
{
	delete timer_;
	timer_ = NULL;
}

void TimerTests::testCreation()
{
	CPPUNIT_ASSERT(!timer_->IsRunning());
}

void TimerTests::testUnregisteredTimer()
{
	timer_->Stop();
	CPPUNIT_ASSERT(!timer_->IsRunning());
}

void TimerTests::testMultipleRegisteredTimer()
{
	timer_->Start();
	timer_->Start();
	timer_->Start();
	CPPUNIT_ASSERT(timer_->IsRunning());
}

void TimerTests::testRegisteredTimer()
{
	timer_->Start();
	CPPUNIT_ASSERT(timer_->IsRunning());
}

void TimerTests::testDeregisteredTimer()
{
	timer_->Start();
	timer_->Stop();
	CPPUNIT_ASSERT(!timer_->IsRunning());
}

void TimerTests::testMultipleDeregisteredTimer()
{
	timer_->Start();
	timer_->Stop();
	timer_->Stop();
	timer_->Stop();
	CPPUNIT_ASSERT(!timer_->IsRunning());
}
