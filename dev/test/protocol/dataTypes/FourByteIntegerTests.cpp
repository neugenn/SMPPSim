#ifndef TWOBYTEINTEGERTESTS_H_
#define TWOBYTEINTEGERTESTS_H_

#include <cppunit/extensions/HelperMacros.h>
#include "Integer.h"

class FourByteIntegerTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(FourByteIntegerTests);
    CPPUNIT_TEST(testSize);
    CPPUNIT_TEST(testInitialData);
    CPPUNIT_TEST(testInitialValue);
    CPPUNIT_TEST(testCreateNullIntegerValue);
    CPPUNIT_TEST(testCreateNullIntegerData);
    CPPUNIT_TEST(testCreateWithNullDataBuffer);
    CPPUNIT_TEST(testSetValue);
    CPPUNIT_TEST(testSetValueData);
    CPPUNIT_TEST(testSetValueOverflow);
    CPPUNIT_TEST(testMaxSize);
    CPPUNIT_TEST_SUITE_END();

    public:
    virtual void setUp();
    virtual void tearDown();

    void testCreateWithNullDataBuffer();
    void testSize();
    void testInitialData();
    void testInitialValue();
    void testCreateNullIntegerValue();
    void testCreateNullIntegerData();
    void testSetValue();
    void testSetValueData();
    void testSetValueOverflow();
    void testMaxSize();

    private:
    SMPP::FourByteInteger* pInt_;

    public:
    static const unsigned char DataBuffer[5];
};

const unsigned char FourByteIntegerTests::DataBuffer[5] = { 0x00, 0x00, 0x00 , 0x20, 0x05};

CPPUNIT_TEST_SUITE_REGISTRATION(FourByteIntegerTests);

void FourByteIntegerTests::setUp()
{
    pInt_ = new SMPP::FourByteInteger(DataBuffer);
    CPPUNIT_ASSERT(NULL != pInt_);
}

void FourByteIntegerTests::tearDown()
{
    delete pInt_;
}

void FourByteIntegerTests::testCreateWithNullDataBuffer()
{
    CPPUNIT_ASSERT_THROW(SMPP::FourByteInteger(NULL, "test"), std::invalid_argument);
}

void FourByteIntegerTests::testSize()
{
    CPPUNIT_ASSERT_EQUAL(size_t(4), pInt_->Size());
}

void FourByteIntegerTests::testInitialData()
{
    std::stringstream s;
    s << *pInt_;
    CPPUNIT_ASSERT_EQUAL(std::string("00000020"), s.str());
}

void FourByteIntegerTests::testInitialValue()
{
    CPPUNIT_ASSERT_EQUAL(uint64_t(32), pInt_->Value());
}

void FourByteIntegerTests::testCreateNullIntegerValue()
{
    SMPP::FourByteInteger i;
    CPPUNIT_ASSERT_EQUAL(SMPP::FourByteInteger::value_t(0), i.Value());
}

void FourByteIntegerTests::testCreateNullIntegerData()
{
    SMPP::FourByteInteger i;
    std::stringstream s;
    s << i;
    CPPUNIT_ASSERT_EQUAL(std::string("00000000"), s.str());
}

void FourByteIntegerTests::testSetValue()
{
    pInt_->SetValue(0x0102);
    CPPUNIT_ASSERT_EQUAL(SMPP::FourByteInteger::value_t(0x0102), pInt_->Value());
}

void FourByteIntegerTests::testSetValueData()
{
    pInt_->SetValue(0x01020304);
    std::stringstream s;
    s << *pInt_;
    CPPUNIT_ASSERT_EQUAL(std::string("01020304"), s.str());
}

void FourByteIntegerTests::testSetValueOverflow()
{
    CPPUNIT_ASSERT_THROW(pInt_->SetValue(0x0102030405LL), std::invalid_argument);
}

void FourByteIntegerTests::testMaxSize()
{
    CPPUNIT_ASSERT_EQUAL(SMPP::FourByteInteger::value_t(0xFFFFFFFF), SMPP::FourByteInteger::MaxValue());
}

#endif // TWOBYTEINTEGERTESTS_H_
