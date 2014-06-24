#ifndef ONEBYTEINTEGERTESTS_H_
#define ONEBYTEINTEGERTESTS_H_

#include <cppunit/extensions/HelperMacros.h>
#include "Integer.h"

class OneByteIntegerTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(OneByteIntegerTests);
    CPPUNIT_TEST(testSize);
    CPPUNIT_TEST(testInitialData);
    CPPUNIT_TEST(testCreateNullIntegerValue);
    CPPUNIT_TEST(testCreateNullIntegerData);
    CPPUNIT_TEST(testCreateWithNullDataBuffer);
    CPPUNIT_TEST(testSetValue);
    CPPUNIT_TEST(testSetValueData);
    CPPUNIT_TEST(testSetValueOverflow);
    CPPUNIT_TEST(testMaxValue);
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
    void testMaxValue();

    private:
    SMPP::OneByteInteger* pInt_;

    public:
    static const unsigned char DataBuffer[1];
};

const unsigned char OneByteIntegerTests::DataBuffer[1] = { 0x01 };

CPPUNIT_TEST_SUITE_REGISTRATION(OneByteIntegerTests);

void OneByteIntegerTests::setUp()
{
    const unsigned char* r = &DataBuffer[0];
    pInt_ = new SMPP::OneByteInteger(r);
    CPPUNIT_ASSERT(NULL != pInt_);
}

void OneByteIntegerTests::tearDown()
{
    delete pInt_;
    pInt_ = NULL;
}

void OneByteIntegerTests::testCreateWithNullDataBuffer()
{
    const unsigned char* r = NULL;
    CPPUNIT_ASSERT_THROW(SMPP::OneByteInteger(r, "test"), std::invalid_argument);
}

void OneByteIntegerTests::testSize()
{
    CPPUNIT_ASSERT_EQUAL(size_t(1), pInt_->Size());
}

void OneByteIntegerTests::testInitialData()
{
    std::stringstream s;
    s << *pInt_;
    CPPUNIT_ASSERT_EQUAL(std::string("01"), s.str());
}

void OneByteIntegerTests::testCreateNullIntegerValue()
{
    SMPP::OneByteInteger i;
    CPPUNIT_ASSERT_EQUAL(SMPP::OneByteInteger::value_t(0), i.Value());
}

void OneByteIntegerTests::testCreateNullIntegerData()
{
    SMPP::OneByteInteger i;
    std::stringstream s;
    s << i;
    CPPUNIT_ASSERT_EQUAL(std::string("00"), s.str());
}

void OneByteIntegerTests::testSetValue()
{
    pInt_->SetValue(0xFF);
    CPPUNIT_ASSERT_EQUAL(SMPP::OneByteInteger::value_t(0xFF), pInt_->Value());
}

void OneByteIntegerTests::testSetValueData()
{
    pInt_->SetValue(0xFF);
    std::stringstream s;
    s << *pInt_;
    CPPUNIT_ASSERT_EQUAL(std::string("FF"), s.str());
}

void OneByteIntegerTests::testSetValueOverflow()
{
    CPPUNIT_ASSERT_THROW(pInt_->SetValue(0x0101), std::invalid_argument);
}

void OneByteIntegerTests::testMaxValue()
{
    CPPUNIT_ASSERT_EQUAL(SMPP::OneByteInteger::value_t(0xFF), SMPP::OneByteInteger::MaxValue());
}

#endif // ONEBYTEINTEGERTESTS_H_
