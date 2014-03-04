#include "TimerTests.h"
#include "timer.h"

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
	CPPUNIT_ASSERT(!timer_->IsActive());
}

void TimerTests::testUnregisteredTimer()
{
	timer_->Stop();
	CPPUNIT_ASSERT(!timer_->IsActive());
}

void TimerTests::testMultipleRegisteredTimer()
{
	timer_->Start();
	timer_->Start();
	timer_->Start();
	CPPUNIT_ASSERT(timer_->IsActive());
}

void TimerTests::testRegisteredTimer()
{
	timer_->Start();
	CPPUNIT_ASSERT(timer_->IsActive());
}

void TimerTests::testDeregisteredTimer()
{
	timer_->Start();
	timer_->Stop();
	CPPUNIT_ASSERT(!timer_->IsActive());
}

void TimerTests::testMultipleDeregisteredTimer()
{
	timer_->Start();
	timer_->Stop();
	timer_->Stop();
	timer_->Stop();
	CPPUNIT_ASSERT(!timer_->IsActive());
}

CPPUNIT_TEST_SUITE_REGISTRATION(TimerTests);

