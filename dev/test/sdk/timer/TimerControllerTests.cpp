#include "TimerControllerTests.h"
#include "TimerController.h"

//CPPUNIT_TEST_SUITE_REGISTRATION(TimerControllerTests);

void TimerControllerTests::setUp()
{
	controller_ = &(SDK::TimerController::GetInstance());
}

void TimerControllerTests::tearDown()
{
	controller_ = NULL;
}

void TimerControllerTests::testCreation()
{
	SDK::TimerController* pc = &(SDK::TimerController::GetInstance());
	CPPUNIT_ASSERT(pc == controller_);
}

void TimerControllerTests::testAddTimer()
{
	SDK::TimerImpl impl;
	CPPUNIT_ASSERT(controller_->Add(&impl));
}

void TimerControllerTests::testAddNullTimer()
{
	CPPUNIT_ASSERT(!controller_->Add(NULL));
}

void TimerControllerTests::testRemoveTimer()
{
	SDK::TimerImpl impl;
	controller_->Add(&impl);
	controller_->Remove(&impl);
	CPPUNIT_ASSERT(!controller_->Manages(impl.GetID()));
}

void TimerControllerTests::testScopeRemoveTimer()
{
	SDK::timer_id_t id = 0;
	{
		SDK::TimerImpl impl;
		controller_->Add(&impl);
		id = impl.GetID();
	}
	CPPUNIT_ASSERT(!controller_->Manages(id));
}
