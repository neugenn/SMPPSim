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
    CPPUNIT_TEST(testSetValueData);
    CPPUNIT_TEST(testSetValueOverflow);
    CPPUNIT_TEST(testGetValue);
    CPPUNIT_TEST_SUITE_END();

    public:
    virtual void setUp();
    virtual void tearDown();

    void testCreateWithNULLDataBuffer();
    void testSize();
    void testGetFormattedData();
    void testCreateNullInteger();
    void testSetValueData();
    void testSetValueOverflow();
    void testGetValue();

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
}

void TwoByteIntegerTests::testCreateWithNULLDataBuffer()
{
    CPPUNIT_ASSERT_THROW(SMPP::TwoByteInteger(NULL, "test"), std::invalid_argument);
}

void TwoByteIntegerTests::testSize()
{
    CPPUNIT_ASSERT_EQUAL(size_t(2), pInt_->Size());
}

void TwoByteIntegerTests::testGetFormattedData()
{
    std::stringstream s;
    s << *pInt_;
    CPPUNIT_ASSERT_EQUAL(std::string("0102"), s.str());
}

void TwoByteIntegerTests::testCreateNullInteger()
{
    SMPP::TwoByteInteger i;
    std::stringstream s;
    s << i;
    CPPUNIT_ASSERT_EQUAL(std::string("0000"), s.str());
}

void TwoByteIntegerTests::testSetValueData()
{
    pInt_->SetValue(0x0102);
    std::stringstream s;
    s << *pInt_;
    CPPUNIT_ASSERT_EQUAL(std::string("0102"), s.str());
}

void TwoByteIntegerTests::testSetValueOverflow()
{
    CPPUNIT_ASSERT_THROW(pInt_->SetValue(0x010203), std::invalid_argument);
}

void TwoByteIntegerTests::testGetValue()
{
    pInt_->SetValue(0x0102);
    CPPUNIT_ASSERT_EQUAL(uint32_t(0x0102), pInt_->Value());
}

#endif // TWOBYTEINTEGERTESTS_H_
