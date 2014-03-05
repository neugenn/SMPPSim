#include <cppunit/extensions/HelperMacros.h>

namespace SDK
{
	class TestTimer;
}

class TimerTests : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TimerTests);
	CPPUNIT_TEST(testCreation);
	CPPUNIT_TEST(testRunningStateForStartedTimer);
	CPPUNIT_TEST(testDefunctStateForStartedTimer);
	CPPUNIT_TEST(testDetachedStateForStartedTimer);
	CPPUNIT_TEST(testRunningStateForStoppedTimer);
	CPPUNIT_TEST(testDefunctStateForStoppedTimer);
	CPPUNIT_TEST(testDetachedStateForStartedScopedTimer);
	CPPUNIT_TEST(testImplForStartedScopedTimer);
	CPPUNIT_TEST(testDefunctStateForStartedScopedTimer);
	CPPUNIT_TEST(testDefaultDefunctStateForTimer);
	CPPUNIT_TEST(testDefaultDetachedStateForTimer);
	CPPUNIT_TEST_SUITE_END();

	public:
		void testCreation();
		void testRunningStateForStartedTimer();
		void testDefunctStateForStartedTimer();
		void testDetachedStateForStartedTimer();
		void testRunningStateForStoppedTimer();
		void testDefunctStateForStoppedTimer();
		void testDetachedStateForStoppedTimer();
		void testDetachedStateForStartedScopedTimer();
		void testDefunctStateForStartedScopedTimer();
		void testDefaultDefunctStateForTimer();
		void testDefaultDetachedStateForTimer();
		void testImplForStartedScopedTimer();

		void setUp();
		void tearDown();

	private:
		SDK::TestTimer* timer_;
};
