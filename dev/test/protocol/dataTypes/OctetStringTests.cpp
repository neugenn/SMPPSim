#ifndef OCTETSTRINGTESTS_H_
#define OCTETSTRINGTESTS_H_

#include "OctetString.h"

#include <cppunit/extensions/HelperMacros.h>


using SMPP::OctetString;

class OctetStringTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(OctetStringTests);
    CPPUNIT_TEST(testCreateWithNULLDataBuffer);
    CPPUNIT_TEST(testNULLOctetString);
    CPPUNIT_TEST(testOperatorEqual);
    CPPUNIT_TEST(testOperatorNotEqual);
    CPPUNIT_TEST(testAssignmentOperator);
    CPPUNIT_TEST_SUITE_END();

    public:
    virtual void setUp();
    virtual void tearDown();
    void testCreateWithNULLDataBuffer();
    void testNULLOctetString();
    void testOperatorEqual();
    void testOperatorNotEqual();
    void testAssignmentOperator();

    private:
    SMPP::OctetString* pString_;

    public:
    static const unsigned char Data[4];
};

const unsigned char OctetStringTests::Data[4] = { 0x01, 0x02, 0x03, 0x04 };

CPPUNIT_TEST_SUITE_REGISTRATION(OctetStringTests);

void OctetStringTests::setUp()
{
    pString_ = new OctetString(Data, 4);
    CPPUNIT_ASSERT(NULL != pString_);
}

void OctetStringTests::tearDown()
{
    delete pString_;
    pString_ = NULL;
}

void OctetStringTests::testCreateWithNULLDataBuffer()
{
    CPPUNIT_ASSERT_THROW(OctetString(NULL, 1), std::invalid_argument);
}

void OctetStringTests::testNULLOctetString()
{
    OctetString os;
    std::stringstream s;
    s << os;
    CPPUNIT_ASSERT_EQUAL(std::string("00"), s.str());
}

void OctetStringTests::testOperatorEqual()
{
    OctetString os1(Data, size_t(4));
    OctetString os2(Data, size_t(4));
    CPPUNIT_ASSERT_EQUAL(os1, os2);
}

void OctetStringTests::testOperatorNotEqual()
{
    OctetString os1(Data, size_t(3));
    OctetString os2(Data, size_t(4));
    CPPUNIT_ASSERT_ASSERTION_FAIL(CPPUNIT_ASSERT_EQUAL(os1, os2));
}

void OctetStringTests::testAssignmentOperator()
{
    OctetString os1(Data, size_t(4));
    OctetString os2(Data, size_t(3));
    os2 = os1;
    CPPUNIT_ASSERT_EQUAL(os1, os2);
}
#endif // OCTETSTRINGTESTS_H_
