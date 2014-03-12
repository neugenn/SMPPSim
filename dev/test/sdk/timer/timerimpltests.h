#ifndef TIMERIMPLTESTS_H
#define TIMERIMPLTESTS_H

#include <cppunit/extensions/HelperMacros.h>

namespace SDK
{
	class TimerImpl;
}

class TimerImplTests : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TimerImplTests);
	CPPUNIT_TEST(testCreation);
	CPPUNIT_TEST(testDefaultSingleshotBehavior);
	CPPUNIT_TEST(testExplicitSingleshotBehavior);
	CPPUNIT_TEST(testDefaultActiveBehavior);
	CPPUNIT_TEST(testExplicitActiveBehavior);
	CPPUNIT_TEST(testExplicitInactiveBehavior);
	CPPUNIT_TEST_SUITE_END();

	public:
		void testCreation();
		void testDefaultSingleshotBehavior();
		void testExplicitSingleshotBehavior();
		void testDefaultActiveBehavior();
		void testExplicitActiveBehavior();
		void testExplicitInactiveBehavior();

		void setUp();
		void tearDown();

	private:
		SDK::TimerImpl* timer_;
};

#endif // TIMERIMPLTESTS_H
