#ifndef ONEBYTEINTEGERTESTS_H_
#define ONEBYTEINTEGERTESTS_H_

#include <cppunit/extensions/HelperMacros.h>
#include "Integer.h"

class OneByteIntegerTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(OneByteIntegerTests);
    CPPUNIT_TEST(testSize);
    CPPUNIT_TEST(testCreateWithNULLDataBuffer);
    CPPUNIT_TEST(testGetFormattedData);
    CPPUNIT_TEST(testCreateNULLInteger);
    CPPUNIT_TEST_SUITE_END();

    public:
    virtual void setUp();
    virtual void tearDown();

    void testCreateWithNULLDataBuffer();
    void testSize();
    void testGetFormattedData();
    void testCreateNULLInteger();

    private:
    SMPP::OneByteInteger* pInt_;

    public:
    static const unsigned char DataBuffer[1];
};

const unsigned char OneByteIntegerTests::DataBuffer[1] = { 0x01u };

CPPUNIT_TEST_SUITE_REGISTRATION(OneByteIntegerTests);

void OneByteIntegerTests::setUp()
{
    pInt_ = new SMPP::OneByteInteger(DataBuffer);
    CPPUNIT_ASSERT(NULL != pInt_);
}

void OneByteIntegerTests::tearDown()
{
    delete pInt_;
    pInt_ = NULL;
}

void OneByteIntegerTests::testCreateWithNULLDataBuffer()
{
    CPPUNIT_ASSERT_THROW(SMPP::OneByteInteger(NULL), std::invalid_argument);
}

void OneByteIntegerTests::testSize()
{
    CPPUNIT_ASSERT_EQUAL(size_t(1), pInt_->Size());
}

void OneByteIntegerTests::testGetFormattedData()
{
    std::string r;
    SMPP::PduDataType::GetFormattedData(pInt_->Data(), pInt_->Size(), r);
    CPPUNIT_ASSERT_EQUAL(std::string("01"), r);
}

void OneByteIntegerTests::testCreateNULLInteger()
{
    SMPP::OneByteInteger i;
    std::string r;
    SMPP::PduDataType::GetFormattedData(i.Data(), i.Size(), r);
    CPPUNIT_ASSERT_EQUAL(std::string("00"), r);
}

#endif // ONEBYTEINTEGERTESTS_H_
