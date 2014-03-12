#include <cppunit/extensions/HelperMacros.h>

namespace SDK
{
	namespace TEST
	{
		class TimerController;
		class Timer;
	}
}

class TimerTests : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TimerTests);
	CPPUNIT_TEST(testCreation);
	CPPUNIT_TEST(testRunningStateForStartedTimer);
	CPPUNIT_TEST(testRunningStateForStoppedTimer);
	CPPUNIT_TEST(testCallbackForElapsedTimer);
	CPPUNIT_TEST(testCallbackForActiveTimer);
	CPPUNIT_TEST(testCallbackForOutOfScopeTimer);
	CPPUNIT_TEST_SUITE_END();

	public:
		void testCreation();
		void testRunningStateForStartedTimer();
		void testRunningStateForStoppedTimer();
		void testCallbackForElapsedTimer();
		void testCallbackForActiveTimer();
		void testCallbackForOutOfScopeTimer();

		void setUp();
		void tearDown();

	private:
		SDK::TEST::TimerController* controller_;
		class TimerObserver;
		TimerObserver* observer_;
		SDK::TEST::Timer* timer_;
};
