#ifndef OCTETSTRINGTESTS_H_
#define OCTETSTRINGTESTS_H_

#include "OctetString.h"

#include <cppunit/extensions/HelperMacros.h>


using SMPP::OctetString;

class OctetStringTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(OctetStringTests);
    CPPUNIT_TEST(testCreateWithNullDataBuffer);
    CPPUNIT_TEST(testNULLOctetString);
    CPPUNIT_TEST(testOperatorEqual);
    CPPUNIT_TEST(testOperatorNotEqual);
    CPPUNIT_TEST(testAssignmentOperator);
    CPPUNIT_TEST_SUITE_END();

    public:
    virtual void setUp();
    virtual void tearDown();
    void testCreateWithNullDataBuffer();
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
    const unsigned char* data = &Data[0];
    pString_ = new OctetString(data, 4);
    CPPUNIT_ASSERT(NULL != pString_);
}

void OctetStringTests::tearDown()
{
    delete pString_;
    pString_ = NULL;
}

void OctetStringTests::testCreateWithNullDataBuffer()
{
    const unsigned char* data = NULL;
    CPPUNIT_ASSERT_THROW(OctetString(data, 1), std::invalid_argument);
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
    const unsigned char* r1 = &Data[0];
    OctetString os1(r1, size_t(4));

    const unsigned char* r2 = &Data[0];
    OctetString os2(r2, size_t(4));
    CPPUNIT_ASSERT_EQUAL(os1, os2);
}

void OctetStringTests::testOperatorNotEqual()
{
    const unsigned char* r1 = &Data[0];
    OctetString os1(r1, size_t(3));

    const unsigned char* r2= &Data[0];
    OctetString os2(r2, size_t(4));

    CPPUNIT_ASSERT_ASSERTION_FAIL(CPPUNIT_ASSERT_EQUAL(os1, os2));
}

void OctetStringTests::testAssignmentOperator()
{
    const unsigned char* r1 = &Data[0];
    OctetString os1(r1, size_t(4));

    const unsigned char* r2 = &Data[0];
    OctetString os2(r2, size_t(3));

    os2 = os1;
    CPPUNIT_ASSERT_EQUAL(os1, os2);
}
#endif // OCTETSTRINGTESTS_H_
