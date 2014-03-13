#include "TimerTests.h"
#include "mocktimer.h"
#include "mocktimercontroller.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TimerTests);

using SDK::TEST::TimerController;
using SDK::TEST::Timer;
using SDK::TimerImpl;
using SDK::SharedPtr;

class TimerTests::TimerObserver : public SDK::TimerCallback
{
	public:
		TimerObserver() : calledBack_(false) {}
		~TimerObserver() {}

		virtual void Elapsed()
		{
			calledBack_ = true;
		}

		bool Notified() const
		{
			return calledBack_;
		}

	private:
		bool calledBack_;
};

void TimerTests::setUp()
{
	controller_ = TimerController::GetTestInstance();
	CPPUNIT_ASSERT(controller_->TimerQueue().empty());

	observer_ = new TimerTests::TimerObserver;
	timer_ = new Timer(observer_);
}

void TimerTests::tearDown()
{
	delete timer_;
	timer_ = NULL;

	delete observer_;
	observer_ = NULL;

	TimerController::ReleaseTestInstance(controller_);
}

void TimerTests::testCreation()
{
	CPPUNIT_ASSERT(NULL !=timer_);
}

void TimerTests::testRunningStateForStartedTimer()
{
	timer_->Start(10);
	CPPUNIT_ASSERT(timer_->IsRunning());
}

void TimerTests::testRunningStateForStoppedTimer()
{
	timer_->Stop();
	CPPUNIT_ASSERT(!timer_->IsRunning());
}

void TimerTests::testCallbackForElapsedTimer()
{
	timer_->Start(10);
	controller_->ProcessQueueWithTimeout();
	CPPUNIT_ASSERT(observer_->Notified());
}

void TimerTests::testCallbackForActiveTimer()
{
	timer_->Start(10);
	controller_->ProcessQueueWithoutTimeout();
	CPPUNIT_ASSERT(!observer_->Notified());
}

void TimerTests::testCallbackForOutOfScopeTimer()
{
	SDK::timer_id_t id;
	TimerObserver o;
	{
		Timer t(&o);
		t.Start(10);
		id = t.GetID();
	}

	controller_->ProcessQueueWithTimeout();
	CPPUNIT_ASSERT(!observer_->Notified());
}
