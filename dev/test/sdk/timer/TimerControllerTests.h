#include <cppunit/extensions/HelperMacros.h>
#include "mocktimercontroller.h"

class TimerControllerTests : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TimerControllerTests);
	CPPUNIT_TEST(testCreation);
	CPPUNIT_TEST(testAddTimer);
	CPPUNIT_TEST(testAddThreeTimers);
	CPPUNIT_TEST(testPriorityWithThreeTimers);
	CPPUNIT_TEST(testPriorityForRestartedTimer);
	/*
	CPPUNIT_TEST(testScopeRemoveTimer);
	*/
	CPPUNIT_TEST_SUITE_END();

	public:
		void testCreation();
		void testAddTimer();
		void testAddThreeTimers();
		void testPriorityWithThreeTimers();
		void testPriorityForRestartedTimer();

		void setUp();
		void tearDown();

	private:
		SDK::TestTimerController* controller_;
		const SDK::TestTimerController::TQueue* timers_;
};
