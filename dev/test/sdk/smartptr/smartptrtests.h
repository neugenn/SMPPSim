#ifndef SHAREDPTRTESTS_H
#define SHAREDPTRTESTS_H

#include <cppunit/extensions/HelperMacros.h>

class SharedPtrTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(SharedPtrTests);
    CPPUNIT_TEST(testCreation);
    CPPUNIT_TEST(testCopyConstruction);
    CPPUNIT_TEST(testCopyConstructionWithSameObject);
    CPPUNIT_TEST(testScopedPtr);
    CPPUNIT_TEST(testSingleNodeSuccess);
    CPPUNIT_TEST(testSingleNodeFail);
    CPPUNIT_TEST(testFirstNodeSuccess);
    CPPUNIT_TEST(testFirstNodeFail);
    CPPUNIT_TEST(testLastNodeSuccess);
    CPPUNIT_TEST(testLastNodeFail);
    /*
    CPPUNIT_TEST(testDefaultSingleshotBehavior);
    CPPUNIT_TEST(testExplicitSingleshotBehavior);
    CPPUNIT_TEST(testDefaultDetachedBehavior);
    CPPUNIT_TEST(testExplicitDetachedBehavior);
    CPPUNIT_TEST(testDefaultDefunctBehavior);
    CPPUNIT_TEST(testExplicitDefunctBehavior);
    CPPUNIT_TEST(testDefaultActiveBehavior);
    CPPUNIT_TEST(testExplicitActiveBehavior);
    CPPUNIT_TEST(testExplicitInactiveBehavior);
    */
    CPPUNIT_TEST_SUITE_END();

    public:
        void testCreation();
    void testCopyConstruction();
    void testCopyConstructionWithSameObject();
    void testScopedPtr();
    void testSingleNodeSuccess();
    void testSingleNodeFail();
    void testFirstNodeSuccess();
    void testFirstNodeFail();
    void testLastNodeSuccess();
    void testLastNodeFail();
    /*
        void testDefaultSingleshotBehavior();
        void testExplicitSingleshotBehavior();
        void testDefaultDetachedBehavior();
        void testExplicitDetachedBehavior();
        void testDefaultDefunctBehavior();
        void testExplicitDefunctBehavior();
        void testDefaultActiveBehavior();
        void testExplicitActiveBehavior();
        void testExplicitInactiveBehavior();
    */
};

#endif // SHAREDPTRTESTS_H
