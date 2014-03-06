#include "TimerControllerTests.h"
#include "mocktimer.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TimerControllerTests);

using SDK::TestTimerController;
using SDK::TestTimer;

void TimerControllerTests::setUp()
{
	TestTimerController::SetTestInstance();
	controller_ = dynamic_cast<TestTimerController*>(&SDK::TimerController::GetInstance());
	timers_ = &(controller_->TimerQueue());
}

void TimerControllerTests::tearDown()
{
	timers_ = NULL;
	controller_ = NULL;
}

void TimerControllerTests::testCreation()
{
	SDK::TimerController* pc = &(SDK::TimerController::GetInstance());
	CPPUNIT_ASSERT(pc == controller_);
}

void TimerControllerTests::testAddTimer()
{
	TestTimer t;
	t.Start(5);
	CPPUNIT_ASSERT(1 == timers_->size());
}

void TimerControllerTests::testAddThreeTimers()
{
	TestTimer t1;
	TestTimer t2;
	TestTimer t3;

	t1.Start(4);
	t2.Start(5);
	t3.Start(6);

	CPPUNIT_ASSERT(3 == timers_->size());
}

void TimerControllerTests::testPriorityWithThreeTimers()
{
	TestTimer t1;
	TestTimer t2;
	TestTimer t3;

	t1.Start(9);
	t2.Start(8);
	t3.Start(6);

	const SDK::TimerImpl* p = timers_->top();
	CPPUNIT_ASSERT(p->GetID() == t3.Impl()->GetID());
}

void TimerControllerTests::testPriorityForRestartedTimer()
{
	TestTimer t1;
	TestTimer t2;

	t1.Start(9);
	t2.Start(8);

	const SDK::TimerImpl* p = timers_->top();
	CPPUNIT_ASSERT(p->GetID() == t2.Impl()->GetID());

	t1.Stop();
	t1.Start(7);

	p = timers_->top();
	CPPUNIT_ASSERT(p->GetID() == t1.Impl()->GetID());
}
