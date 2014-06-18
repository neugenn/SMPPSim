#ifndef TWOBYTEINTEGERTESTS_H_
#define TWOBYTEINTEGERTESTS_H_

#include <cppunit/extensions/HelperMacros.h>
#include "Integer.h"

class TwoByteIntegerTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TwoByteIntegerTests);
    CPPUNIT_TEST(testSize);
    CPPUNIT_TEST(testInitialData);
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
    void testCreateNullIntegerValue();
    void testCreateNullIntegerData();
    void testSetValue();
    void testSetValueData();
    void testSetValueOverflow();
    void testMaxSize();

    private:
    SMPP::TwoByteInteger* pInt_;

    public:
    static const unsigned char DataBuffer[3];
};

const unsigned char TwoByteIntegerTests::DataBuffer[3] = { 0x01, 0x02, 0x03 };

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

void TwoByteIntegerTests::testCreateWithNullDataBuffer()
{
    CPPUNIT_ASSERT_THROW(SMPP::TwoByteInteger(NULL, "test"), std::invalid_argument);
}

void TwoByteIntegerTests::testSize()
{
    CPPUNIT_ASSERT_EQUAL(size_t(2), pInt_->Size());
}

void TwoByteIntegerTests::testInitialData()
{
    std::stringstream s;
    s << *pInt_;
    CPPUNIT_ASSERT_EQUAL(std::string("0102"), s.str());
}

void TwoByteIntegerTests::testCreateNullIntegerValue()
{
    SMPP::TwoByteInteger i;
    CPPUNIT_ASSERT_EQUAL(SMPP::TwoByteInteger::value_t(0), i.Value());
}

void TwoByteIntegerTests::testCreateNullIntegerData()
{
    SMPP::TwoByteInteger i;
    std::stringstream s;
    s << i;
    CPPUNIT_ASSERT_EQUAL(std::string("0000"), s.str());
}

void TwoByteIntegerTests::testSetValue()
{
    pInt_->SetValue(0x0102);
    CPPUNIT_ASSERT_EQUAL(SMPP::TwoByteInteger::value_t(0x0102), pInt_->Value());
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

void TwoByteIntegerTests::testMaxSize()
{
    CPPUNIT_ASSERT_EQUAL(SMPP::TwoByteInteger::value_t(0xFFFF), SMPP::TwoByteInteger::MaxValue());
}

#endif // TWOBYTEINTEGERTESTS_H_
