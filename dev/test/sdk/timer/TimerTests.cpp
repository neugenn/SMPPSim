#include "TimerTests.h"
#include "mocktimer.h"
#include "mocktimercontroller.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TimerTests);

using SDK::TimerImpl;
using SDK::TestTimer;
using SDK::TestTimerController;

void TimerTests::setUp()
{
	timer_ = new SDK::TestTimer();
	TestTimerController::SetTestInstance();
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

void TimerTests::testRunningStateForStartedTimer()
{
	timer_->Start();
	CPPUNIT_ASSERT(timer_->IsRunning());
}

void TimerTests::testDefunctStateForStartedTimer()
{
	timer_->Start();
	const TimerImpl* pi = timer_->Impl();
	CPPUNIT_ASSERT(!pi->IsDefunct());
}

void TimerTests::testDetachedStateForStartedTimer()
{
	timer_->Start();
	const TimerImpl* pi = timer_->Impl();
	CPPUNIT_ASSERT(pi->IsDetached());
}

void TimerTests::testRunningStateForStoppedTimer()
{
	timer_->Start();
	timer_->Stop();
	CPPUNIT_ASSERT(!timer_->IsRunning());
}

void TimerTests::testDefunctStateForStoppedTimer()
{
	timer_->Start();
	timer_->Stop();
	const TimerImpl* pi = timer_->Impl();
	CPPUNIT_ASSERT(!pi->IsDefunct());
}

void TimerTests::testDetachedStateForStoppedTimer()
{
	timer_->Start();
	timer_->Stop();
	const TimerImpl* pi = timer_->Impl();
	CPPUNIT_ASSERT(pi->IsDetached());
}

void TimerTests::testImplForStartedScopedTimer()
{
	const TimerImpl* pi = NULL;
	{
		TestTimer t;
		t.Start();
		pi = t.Impl();
	}
	CPPUNIT_ASSERT(NULL != pi);
}

void TimerTests::testDetachedStateForStartedScopedTimer()
{
	const TimerImpl* pi = NULL;
	{
		TestTimer t;
		t.Start();
		pi = t.Impl();
	}
	CPPUNIT_ASSERT(pi->IsDetached());
}

void TimerTests::testDefunctStateForStartedScopedTimer()
{
	const TimerImpl* pi = NULL;
	{
		TestTimer t;
		t.Start();
		pi = t.Impl();
	}
	CPPUNIT_ASSERT(pi->IsDefunct());
}

void TimerTests::testDefaultDefunctStateForTimer()
{
	const TimerImpl* pi = timer_->Impl();
	CPPUNIT_ASSERT(!pi->IsDefunct());
}

void TimerTests::testDefaultDetachedStateForTimer()
{
	const TimerImpl* pi = timer_->Impl();
	CPPUNIT_ASSERT(!pi->IsDetached());
}
