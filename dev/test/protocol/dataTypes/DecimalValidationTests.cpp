#ifndef DECIMALVALIDATIONTESTS_H_
#define DECIMALVALIDATIONTESTS_H_

#include "DecimalValidation.h"

#include <cppunit/extensions/HelperMacros.h>

class DecimalValidationTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(DecimalValidationTests);
    CPPUNIT_TEST(testValidAsciiDecimalData);
    CPPUNIT_TEST(testValidAsciiNonDecimalData);
    CPPUNIT_TEST(testInvalidAsciiData);
    CPPUNIT_TEST_SUITE_END();

    public:
    virtual void setUp();
    virtual void tearDown();
    void testValidAsciiDecimalData();
    void testValidAsciiNonDecimalData();
    void testInvalidAsciiData();

    private:
    SMPP::Validation* pValidation_;

    public:
    static const unsigned char ValidAsciiDecimalData[10];
    static const unsigned char ValidAsciiNonDecimalData[5];
    static const unsigned char InvalidAsciiData[5];
};

const unsigned char DecimalValidationTests::ValidAsciiDecimalData[10] =
{
    0x30,	0x31,	0x32,	0x33,
    0x34,	0x35,	0x36,	0x37,
    0x38,	0x39
};

const unsigned char DecimalValidationTests::ValidAsciiNonDecimalData[5] = { 0x40, 0x42, 0x35, 0x38, 0x39 };
const unsigned char DecimalValidationTests::InvalidAsciiData[5] = { 0x31, 0x55, 0x8F, 0x00, 0x90 };

CPPUNIT_TEST_SUITE_REGISTRATION(DecimalValidationTests);

void DecimalValidationTests::setUp()
{
    pValidation_ = new SMPP::DecimalValidation;
    CPPUNIT_ASSERT(NULL != pValidation_);
}

void DecimalValidationTests::tearDown()
{
    delete pValidation_;
}

void DecimalValidationTests::testValidAsciiDecimalData()
{
    CPPUNIT_ASSERT_EQUAL(true, pValidation_->IsValid(&ValidAsciiDecimalData[0], 10));
}

void DecimalValidationTests::testValidAsciiNonDecimalData()
{
    CPPUNIT_ASSERT_EQUAL(false, pValidation_->IsValid(&ValidAsciiNonDecimalData[0], 5));
}

void DecimalValidationTests::testInvalidAsciiData()
{
    CPPUNIT_ASSERT_EQUAL(false, pValidation_->IsValid(&InvalidAsciiData[0], 5));
}

#endif // DECIMALVALIDATIONTESTS_H_
