#include "smartptrtests.h"
#include "sharedptr.h"

using SDK::SharedPtr;

CPPUNIT_TEST_SUITE_REGISTRATION(SharedPtrTests);

void SharedPtrTests::testCreation()
{
    SharedPtr<int> p(new int(1));
    CPPUNIT_ASSERT(1 == p.Counter());
}

void SharedPtrTests::testCopyConstruction()
{
    SharedPtr<int> p(new int(1));
    SharedPtr<int> p1(p);

    CPPUNIT_ASSERT(2 == p1.Counter());
}

void SharedPtrTests::testCopyConstructionWithSameObject()
{
    SharedPtr<int> p(new int(1));
    SharedPtr<int> p1(p);
    SharedPtr<int> p2(p);
    SharedPtr<int> p3(p);

    CPPUNIT_ASSERT(4 == p2.Counter());
}

void SharedPtrTests::testScopedPtr()
{
    SharedPtr<int> p1(new int(1));
    {
    SharedPtr<int> p2(p1);
    }

    CPPUNIT_ASSERT(1 == p1.Counter());
}

void SharedPtrTests::testSingleNodeSuccess()
{
    SharedPtr<int> p1(new int(1));
    CPPUNIT_ASSERT(p1.IsSingleNode());
}

void SharedPtrTests::testSingleNodeFail()
{
    SharedPtr<int> p1(new int(1));
    SharedPtr<int> p2(p1);
    CPPUNIT_ASSERT(!p1.IsSingleNode());
}

void SharedPtrTests::testFirstNodeSuccess()
{
    SharedPtr<int> p1(new int(1));
    SharedPtr<int> p2(p1);
    CPPUNIT_ASSERT(p1.IsFirstNode());
}

void SharedPtrTests::testFirstNodeFail()
{
    SharedPtr<int> p1(new int(1));
    SharedPtr<int> p2(p1);
    CPPUNIT_ASSERT(!p2.IsFirstNode());
}

void SharedPtrTests::testLastNodeSuccess()
{
    SharedPtr<int> p1(new int(1));
    SharedPtr<int> p2(p1);
    CPPUNIT_ASSERT(p2.IsLastNode());
}

void SharedPtrTests::testLastNodeFail()
{
    SharedPtr<int> p1(new int(1));
    SharedPtr<int> p2(p1);
    CPPUNIT_ASSERT(!p1.IsLastNode());
}
