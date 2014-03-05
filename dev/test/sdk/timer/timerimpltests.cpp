#include "timerimpltests.h"
#include "timerimpl.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TimerImplTests);

using SDK::TimerImpl;

void TimerImplTests::setUp()
{
	timer_ = new TimerImpl;
}

void TimerImplTests::tearDown()
{
	delete timer_;
	timer_ = NULL;
}

void TimerImplTests::testCreation()
{
	CPPUNIT_ASSERT(NULL != timer_);
}

void TimerImplTests::testDefaultSingleshotBehavior()
{
	CPPUNIT_ASSERT(!timer_->IsSingleShot());
}


void TimerImplTests::testExplicitSingleshotBehavior()
{
	timer_->EnableSingleShot();
	CPPUNIT_ASSERT(timer_->IsSingleShot());
}

void TimerImplTests::testDefaultDetachedBehavior()
{
	CPPUNIT_ASSERT(!timer_->IsDetached());
}

void TimerImplTests::testExplicitDetachedBehavior()
{
	timer_->SetDetached();
	CPPUNIT_ASSERT(timer_->IsDetached());
}

void TimerImplTests::testDefaultDefunctBehavior()
{
	CPPUNIT_ASSERT(!timer_->IsDefunct());
}

void TimerImplTests::testExplicitDefunctBehavior()
{
	timer_->SetDefunct();
	CPPUNIT_ASSERT(timer_->IsDefunct());
}

void TimerImplTests::testDefaultActiveBehavior()
{
	CPPUNIT_ASSERT(!timer_->IsActive());
}

void TimerImplTests::testExplicitActiveBehavior()
{
	timer_->SetActive();
	CPPUNIT_ASSERT(timer_->IsActive());
}

void TimerImplTests::testExplicitInactiveBehavior()
{
	timer_->SetInactive();
	CPPUNIT_ASSERT(!timer_->IsActive());
}
