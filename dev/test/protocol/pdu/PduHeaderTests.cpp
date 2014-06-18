#ifndef PDUHEADERTESTS_H_
#define PDUHEADERTESTS_H_

#include "PduHeader.h"
#include <cppunit/extensions/HelperMacros.h>

class PduHeaderTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(PduHeaderTests);
    CPPUNIT_TEST(testCreateWithNULLDataBuffer);
    CPPUNIT_TEST(testFormattedData);
    CPPUNIT_TEST(testSize);
    CPPUNIT_TEST(testOperatorEqual);
    CPPUNIT_TEST(testOperatorNotEqual);
    CPPUNIT_TEST(testEmptyHeader);
    CPPUNIT_TEST_SUITE_END();

    public:
    virtual void setUp();
    virtual void tearDown();
    void testCreateWithNULLDataBuffer();
    void testFormattedData();
    void testSize();
    void testOperatorEqual();
    void testOperatorNotEqual();
    void testEmptyHeader();

    private:
    PduHeader* pHeader_;

    private:
    static const unsigned char Data[16];
};

const unsigned char PduHeaderTests::Data[16] = {
        0x00, 0x00, 0x00, 0x10,
        0x00, 0x00, 0x00, 0x01, //BindReceiver
        0x00, 0x00, 0x00, 0x00, //CommandStatus
        0x00, 0x00, 0x00, 0x01, //Sequence number
};

CPPUNIT_TEST_SUITE_REGISTRATION(PduHeaderTests);

void PduHeaderTests::setUp()
{
    pHeader_ = new PduHeader(Data);
    CPPUNIT_ASSERT(NULL != pHeader_);
}

void PduHeaderTests::tearDown()
{
    delete pHeader_;
}

void PduHeaderTests::testFormattedData()
{
    std::stringstream s;
    s << *pHeader_;
    CPPUNIT_ASSERT_EQUAL(std::string("00000010000000010000000000000001"), s.str());
}

void PduHeaderTests::testSize()
{
    CPPUNIT_ASSERT_EQUAL(size_t(16), pHeader_->Size());
}

void PduHeaderTests::testCreateWithNULLDataBuffer()
{
    CPPUNIT_ASSERT_THROW(PduHeader(NULL), std::invalid_argument);
}

void PduHeaderTests::testOperatorEqual()
{
    PduHeader h1(Data);
    PduHeader h2(Data);
    CPPUNIT_ASSERT_EQUAL(h1, h2);
}

void PduHeaderTests::testOperatorNotEqual()
{
    PduHeader h1(Data);
    PduHeader h2(Data + 1);
    CPPUNIT_ASSERT(h1 != h2);
}

void PduHeaderTests::testEmptyHeader()
{
    PduHeader h;
    std::stringstream s;
    s << h;
    CPPUNIT_ASSERT_EQUAL(std::string("00000000000000000000000000000000"), s.str());
}

#endif // PDUHEADERTESTS_H_
