#ifndef SHAREDPTRTESTS_H
#define SHAREDPTRTESTS_H

#include <cppunit/extensions/HelperMacros.h>

class SharedPtrTests : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(SharedPtrTests);
	CPPUNIT_TEST(testCreation);
	CPPUNIT_TEST(testCopyConstruction);
	CPPUNIT_TEST(testAssignment);
	CPPUNIT_TEST(testSelfAssignment);
	CPPUNIT_TEST(testScopedPtr);
	CPPUNIT_TEST(testVectorBehavior);
	CPPUNIT_TEST(testSingleNodeSuccess);
	CPPUNIT_TEST(testSingleNodeFail);
	CPPUNIT_TEST(testDereferencing);
	CPPUNIT_TEST_SUITE_END();

	public:
		void testCreation();
		void testCopyConstruction();
		void testScopedPtr();
		void testSingleNodeSuccess();
		void testSingleNodeFail();
		void testVectorBehavior();
		void testAssignment();
		void testSelfAssignment();
		void testDereferencing();
};

#endif // SHAREDPTRTESTS_H
