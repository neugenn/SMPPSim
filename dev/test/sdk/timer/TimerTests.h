#include <cppunit/extensions/HelperMacros.h>

namespace SDK
{
	class Timer;
}

class TimerTests : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TimerTests);
	CPPUNIT_TEST(testCreation);
	CPPUNIT_TEST(testUnregisteredTimer);
	CPPUNIT_TEST(testRegisteredTimer);
	CPPUNIT_TEST(testMultipleRegisteredTimer);
	CPPUNIT_TEST(testDeregisteredTimer);
	CPPUNIT_TEST(testMultipleDeregisteredTimer);
	CPPUNIT_TEST_SUITE_END();

	public:
		void testCreation();
		void testUnregisteredTimer();
		void testRegisteredTimer();
		void testMultipleRegisteredTimer();
		void testDeregisteredTimer();
		void testMultipleDeregisteredTimer();

		void setUp();
		void tearDown();

	private:
		SDK::Timer* timer_;
};


