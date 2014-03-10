#include "smartptrtests.h"
#include "sharedptr.h"
#include <vector>

using SDK::SharedPtr;

CPPUNIT_TEST_SUITE_REGISTRATION(SharedPtrTests);

void SharedPtrTests::testCreation()
{
	SharedPtr<int> p(new int(1));
	CPPUNIT_ASSERT(1 == p.Counter());
}

void SharedPtrTests::testCopyConstruction()
{
	SharedPtr<int> p1(new int(1));
	SharedPtr<int> p2(p1);
	CPPUNIT_ASSERT(2 == p1.Counter());
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
	SharedPtr<int> p(new int(1));
	CPPUNIT_ASSERT(p.IsSingleNode());
}

void SharedPtrTests::testSingleNodeFail()
{
	SharedPtr<int> p1(new int(1));
	SharedPtr<int> p2(p1);
	CPPUNIT_ASSERT(!p1.IsSingleNode());
}

void SharedPtrTests::testVectorBehavior()
{
	SharedPtr<int> p(new int(1));

	std::vector<SharedPtr<int> > v;
	const size_t count = 10;
	for (size_t i = 0; i < count; ++i)
	{
		v.push_back(p);
	}

	CPPUNIT_ASSERT(count + 1 == p.Counter());
}

void SharedPtrTests::testAssignment()
{
	SharedPtr<int> p1(new int(1));
	SharedPtr<int> p2;

	p2 = p1;
	CPPUNIT_ASSERT(2 == p1.Counter());
}

void SharedPtrTests::testSelfAssignment()
{
	SharedPtr<int> p(new int(1));
	p = p;
	CPPUNIT_ASSERT(1 == p.Counter());
}

void SharedPtrTests::testDereferencing()
{
	SharedPtr<int> p(new int(1));
	int i = *p;
	CPPUNIT_ASSERT_EQUAL(1, i);
}
