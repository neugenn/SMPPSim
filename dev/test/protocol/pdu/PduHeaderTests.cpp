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
    CPPUNIT_TEST_SUITE_END();

    public:
    virtual void setUp();
    virtual void tearDown();
    void testCreateWithNULLDataBuffer();
    void testFormattedData();
    void testSize();

    private:
    SMPP::PduHeader* pHeader_;

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
    pHeader_ = new SMPP::PduHeader(Data);
    CPPUNIT_ASSERT(NULL != pHeader_);
}

void PduHeaderTests::tearDown()
{
    delete pHeader_;
}

void PduHeaderTests::testFormattedData()
{
    std::string r;
    SMPP::PduDataType::GetFormattedData(pHeader_->Data(), pHeader_->Size(), r);
    CPPUNIT_ASSERT_EQUAL(std::string("00000010000000010000000000000001"), r);
}

void PduHeaderTests::testSize()
{
    CPPUNIT_ASSERT_EQUAL(size_t(16), pHeader_->Size());
}

void PduHeaderTests::testCreateWithNULLDataBuffer()
{
    CPPUNIT_ASSERT_THROW(SMPP::PduHeader(NULL), std::invalid_argument);
}

#endif // PDUHEADERTESTS_H_
