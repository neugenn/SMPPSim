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
	timer_->Start(10);
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
	CPPUNIT_ASSERT(timer_->IsRunning());
}

void TimerTests::testRunningStateForStartedTimer()
{
	CPPUNIT_ASSERT(timer_->IsRunning());
}

void TimerTests::testRunningStateForStoppedTimer()
{
	timer_->Stop();
	CPPUNIT_ASSERT(!timer_->IsRunning());
}

void TimerTests::testCallbackForElapsedTimer()
{
	controller_->GetCondVar().SetTmoResponse(true);
	controller_->RunEventLoop();

	CPPUNIT_ASSERT(observer_->Notified());
}

void TimerTests::testCallbackForActiveTimer()
{
	controller_->GetCondVar().SetTmoResponse(false);
	controller_->RunEventLoop();

	CPPUNIT_ASSERT(!observer_->Notified());
}

void TimerTests::testCallbackForOutOfScopeTimer()
{
	TimerObserver o;
	{
		Timer t(&o);
		t.Start(10);
	}

	controller_->RunEventLoop();
	CPPUNIT_ASSERT(!observer_->Notified());
}
