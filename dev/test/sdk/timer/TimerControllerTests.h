#include <cppunit/extensions/HelperMacros.h>

namespace SDK
{
	class TimerController;
}

class TimerControllerTests : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TimerControllerTests);
	CPPUNIT_TEST(testCreation);
	CPPUNIT_TEST(testAddTimer);
	CPPUNIT_TEST(testAddNullTimer);
	CPPUNIT_TEST(testRemoveTimer);
	CPPUNIT_TEST(testScopeRemoveTimer);
	CPPUNIT_TEST_SUITE_END();

	public:
		void testCreation();
		void testAddTimer();
		void testAddNullTimer();
		void testRemoveTimer();
		void testScopeRemoveTimer();

		void setUp();
		void tearDown();

	private:
		SDK::TimerController* controller_;
};
