#include <cppunit/extensions/HelperMacros.h>
#include "mocktimercontroller.h"

class TimerControllerTests : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TimerControllerTests);
	CPPUNIT_TEST(testCreation);
	CPPUNIT_TEST(testAddTimer);
	CPPUNIT_TEST(testPriority);
	CPPUNIT_TEST(testPriorityForRestartedTimer);
	CPPUNIT_TEST(testProcessedQueuePriority);
	CPPUNIT_TEST(testProcessedQueueSizeForOutOfScopeTimer);
	CPPUNIT_TEST(testProcessedQueueSizeForElapsedTimer);
	CPPUNIT_TEST(testProcessedQueueSizeForStoppedTimer);
	CPPUNIT_TEST(testQueueSizeForOutOfScopeTimer);
	CPPUNIT_TEST(testQueueSizeForElapsedTimer);
	CPPUNIT_TEST(testQueueSizeForStoppedTimer);
	CPPUNIT_TEST(testQueueSizeForRestartedTimer);
	CPPUNIT_TEST(testQueueSizeForSingleShotTimer);
	CPPUNIT_TEST_SUITE_END();

	public:
		void testCreation();
		void testAddTimer();
		void testPriority();
		void testPriorityForRestartedTimer();
		void testProcessedQueuePriority();
		void testProcessedQueueSizeForOutOfScopeTimer();
		void testProcessedQueueSizeForStoppedTimer();
		void testProcessedQueueSizeForElapsedTimer();
		void testQueueSizeForOutOfScopeTimer();
		void testQueueSizeForStoppedTimer();
		void testQueueSizeForElapsedTimer();
		void testQueueSizeForRestartedTimer();
		void testQueueSizeForSingleShotTimer();

		void setUp();
		void tearDown();

	private:
		SDK::TEST::TimerController* controller_;
		const SDK::TimerController::TQueue* timers_;
};
