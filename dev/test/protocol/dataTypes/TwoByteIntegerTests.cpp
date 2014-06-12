#ifndef TWOBYTEINTEGERTESTS_H_
#define TWOBYTEINTEGERTESTS_H_

#include <cppunit/extensions/HelperMacros.h>
#include "Integer.h"

class TwoByteIntegerTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TwoByteIntegerTests);
    CPPUNIT_TEST(testSize);
    CPPUNIT_TEST(testCreateWithNULLDataBuffer);
    CPPUNIT_TEST(testGetFormattedData);
    CPPUNIT_TEST(testCreateNullInteger);
    CPPUNIT_TEST_SUITE_END();

    public:
    virtual void setUp();
    virtual void tearDown();

    void testCreateWithNULLDataBuffer();
    void testSize();
    void testGetFormattedData();
    void testCreateNullInteger();

    private:
    SMPP::TwoByteInteger* pInt_;

    public:
    static const unsigned char DataBuffer[3];
};

const unsigned char TwoByteIntegerTests::DataBuffer[3] = { 0x01u, 0x02u, 0x03u };

CPPUNIT_TEST_SUITE_REGISTRATION(TwoByteIntegerTests);

void TwoByteIntegerTests::setUp()
{
    pInt_ = new SMPP::TwoByteInteger(DataBuffer);
    CPPUNIT_ASSERT(NULL != pInt_);
}

void TwoByteIntegerTests::tearDown()
{
    delete pInt_;
    pInt_ = NULL;
}

void TwoByteIntegerTests::testCreateWithNULLDataBuffer()
{
    CPPUNIT_ASSERT_THROW(SMPP::TwoByteInteger(NULL), std::invalid_argument);
}

void TwoByteIntegerTests::testSize()
{
    CPPUNIT_ASSERT_EQUAL(size_t(2), pInt_->Size());
}

void TwoByteIntegerTests::testGetFormattedData()
{
    std::string r;
    SMPP::PduDataType::GetFormattedData(pInt_->Data(), pInt_->Size(), r);
    CPPUNIT_ASSERT_EQUAL(std::string("0102"), r);
}

void TwoByteIntegerTests::testCreateNullInteger()
{
    SMPP::TwoByteInteger i;
    std::string r;
    SMPP::PduDataType::GetFormattedData(i.Data(), i.Size(), r);
    CPPUNIT_ASSERT_EQUAL(std::string("0000"), r);
}

#endif // TWOBYTEINTEGERTESTS_H_
