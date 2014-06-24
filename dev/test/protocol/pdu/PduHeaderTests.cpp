#ifndef PDUHEADERTESTS_H_
#define PDUHEADERTESTS_H_

#include "PduHeader.h"
#include <cppunit/extensions/HelperMacros.h>

class PduHeaderTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(PduHeaderTests);
    CPPUNIT_TEST(testCreateWithNullData);
    CPPUNIT_TEST(testEmptyHeader);
    CPPUNIT_TEST(testData);
    CPPUNIT_TEST(testSize);
    CPPUNIT_TEST(testOperatorEqual);
    CPPUNIT_TEST(testOperatorNotEqual);
    CPPUNIT_TEST(testCommandLen);
    CPPUNIT_TEST(testCommandId);
    CPPUNIT_TEST(testCommandStatus);
    CPPUNIT_TEST(testSequence);
    CPPUNIT_TEST_SUITE_END();

    public:
    virtual void setUp();
    virtual void tearDown();
    void testCreateWithNullData();
    void testEmptyHeader();
    void testData();
    void testSize();
    void testOperatorEqual();
    void testOperatorNotEqual();
    void testCommandLen();
    void testCommandId();
    void testCommandStatus();
    void testSequence();

    private:
    PduHeader* pHeader_;

    private:
    static const unsigned char Data[20];
};

const unsigned char PduHeaderTests::Data[20] = {
        0x00, 0x00, 0x00, 0x10, //command_len
        0x00, 0x00, 0x00, 0x01, //command_id (BIND_RECEIVER)
        0x00, 0x00, 0x00, 0x04, //command_status (ESME_RINVBNDSTS)
        0x00, 0x00, 0x00, 0x04, //sequence_number
        0x01, 0x02, 0x03, 0x04 //other data
};

CPPUNIT_TEST_SUITE_REGISTRATION(PduHeaderTests);

void PduHeaderTests::setUp()
{
    const unsigned char* r = &Data[0];
    pHeader_ = new PduHeader(r);
    CPPUNIT_ASSERT(NULL != pHeader_);
}

void PduHeaderTests::tearDown()
{
    delete pHeader_;
}

void PduHeaderTests::testData()
{
    std::stringstream s;
    s << *pHeader_;
    CPPUNIT_ASSERT_EQUAL(std::string("00000010000000010000000400000004"), s.str());
}

void PduHeaderTests::testSize()
{
    CPPUNIT_ASSERT_EQUAL(size_t(16), pHeader_->Size());
}

void PduHeaderTests::testCreateWithNullData()
{
    const unsigned char* r = NULL;
    CPPUNIT_ASSERT_THROW(new PduHeader(r), std::invalid_argument);
}

void PduHeaderTests::testOperatorEqual()
{
    const unsigned char* r1 = &Data[0];
    PduHeader h1(r1);

    const unsigned char* r2 = &Data[0];
    PduHeader h2(r2);
    CPPUNIT_ASSERT_EQUAL(h1, h2);
}

void PduHeaderTests::testOperatorNotEqual()
{
    const unsigned char* r1 = &Data[0];
    PduHeader h1(r1);

    const unsigned char* r2 = &Data[1];
    PduHeader h2(r2);
    CPPUNIT_ASSERT(h1 != h2);
}

void PduHeaderTests::testEmptyHeader()
{
    PduHeader h;
    std::stringstream s;
    s << h;
    CPPUNIT_ASSERT_EQUAL(std::string("00000000000000000000000000000000"), s.str());
}

void PduHeaderTests::testCommandLen()
{
    CPPUNIT_ASSERT_EQUAL(SMPP::FourByteInteger::value_t(0x00000010), pHeader_->CommandLength());
}

void PduHeaderTests::testCommandId()
{
    CPPUNIT_ASSERT_EQUAL(SMPP::BIND_RECEIVER, pHeader_->CommandId());
}

void PduHeaderTests::testCommandStatus()
{
    CPPUNIT_ASSERT_EQUAL(SMPP::ESME_RINVBNDSTS, pHeader_->CommandStatus());
}

void PduHeaderTests::testSequence()
{
    CPPUNIT_ASSERT_EQUAL(SMPP::FourByteInteger::value_t(0x00000004), pHeader_->SequenceNumber());
}

#endif // PDUHEADERTESTS_H_
