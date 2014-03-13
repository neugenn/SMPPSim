#include "TimerControllerTests.h"
#include "mocktimer.h"
#include <iostream>

CPPUNIT_TEST_SUITE_REGISTRATION(TimerControllerTests);

using SDK::TEST::TimerController;
using SDK::TEST::Timer;
using SDK::SharedPtr;
using SDK::TimerImpl;

void TimerControllerTests::setUp()
{
	controller_ = TimerController::GetTestInstance();
	timers_ = &(controller_->TimerQueue());
	CPPUNIT_ASSERT(timers_->empty());
}

void TimerControllerTests::tearDown()
{
	timers_ = NULL;
	TimerController::ReleaseTestInstance(controller_);
}

void TimerControllerTests::testCreation()
{
	SDK::TimerController* pc = &(SDK::TimerController::GetInstance());
	CPPUNIT_ASSERT(pc == controller_);
}

void TimerControllerTests::testAddTimer()
{
	Timer t1;
	t1.Start(5);

	Timer t2;
	t2.Start(9);
	CPPUNIT_ASSERT(2 == timers_->size());
}

void TimerControllerTests::testPriority()
{
	Timer t1;
	t1.Start(9);

	Timer t2;
	t2.Start(8);

	Timer t3;
	t3.Start(6);

	const SharedPtr<TimerImpl>& firstToElapse = timers_->top();
	CPPUNIT_ASSERT(firstToElapse->GetID() == t3.GetID());
}

void TimerControllerTests::testPriorityForRestartedTimer()
{
	Timer t1;
	t1.Start(9);

	Timer t2;
	t2.Start(8);

	const SharedPtr<TimerImpl>& firstToElapse = timers_->top();
	CPPUNIT_ASSERT(firstToElapse->GetID() == t2.GetID());

	t1.Stop();
	t1.Start(7);

	controller_->ProcessQueueWithTimeout();
	const SharedPtr<TimerImpl>& firstToElapseAfterRestart = timers_->top();
	CPPUNIT_ASSERT(firstToElapseAfterRestart->GetID() == t1.GetID());
}

void TimerControllerTests::testQueueSizeForRestartedTimer()
{
	Timer t1;
	t1.Start(9);

	Timer t2;
	t2.Start(8);

	t1.Stop();
	t1.Start(7);

	CPPUNIT_ASSERT(3 == timers_->size());
}

void TimerControllerTests::testProcessedQueuePriority()
{
	Timer t1;
	t1.Start(4);

	Timer t2;
	t2.Start(2);

	controller_->ProcessQueueWithTimeout();
	controller_->ProcessQueueWithTimeout();

	const SharedPtr<TimerImpl>& firstToExpire = timers_->top();
	CPPUNIT_ASSERT(firstToExpire->GetID() == t2.GetID());
}

void TimerControllerTests::testProcessedQueueSizeForOutOfScopeTimer()
{
	{
		Timer t;
		t.Start(9);
	}

	controller_->ProcessQueueWithTimeout();
	CPPUNIT_ASSERT(0 == timers_->size());
}

void TimerControllerTests::testProcessedQueueSizeForStoppedTimer()
{
	Timer t;
	t.Start(9);
	t.Stop();

	controller_->ProcessQueueWithTimeout();
	CPPUNIT_ASSERT(0 == timers_->size());
}

void TimerControllerTests::testProcessedQueueSizeForElapsedTimer()
{
	Timer t;
	t.Start(9);

	controller_->ProcessQueueWithTimeout();

	CPPUNIT_ASSERT(1 == timers_->size());
}

void TimerControllerTests::testQueueSizeForOutOfScopeTimer()
{
	{
		Timer t;
		t.Start(9);
	}

	CPPUNIT_ASSERT(1 == timers_->size());
}

void TimerControllerTests::testQueueSizeForStoppedTimer()
{
	Timer t;
	t.Start(9);
	t.Stop();

	CPPUNIT_ASSERT(1 == timers_->size());
}

void TimerControllerTests::testQueueSizeForElapsedTimer()
{
	Timer t;
	t.Start(9);

	CPPUNIT_ASSERT(1 == timers_->size());
}

void TimerControllerTests::testQueueSizeForSingleShotTimer()
{
	Timer t;
	t.Impl()->EnableSingleShot();
	t.Start(9);
	controller_->ProcessQueueWithTimeout();

	CPPUNIT_ASSERT(0 == timers_->size());
}
