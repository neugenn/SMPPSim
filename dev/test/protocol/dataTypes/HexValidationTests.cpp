#ifndef HEXVALIDATIONTESTS_H_
#define HEXVALIDATIONTESTS_H_

#include <cppunit/extensions/HelperMacros.h>
#include "HexValidation.h"

class HexValidationTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(HexValidationTests);
    CPPUNIT_TEST(testValidAsciiHexDigitData);
    CPPUNIT_TEST(testInvalidAsciiHexDigitData);
    CPPUNIT_TEST(testInvalidAsciiData);
    CPPUNIT_TEST_SUITE_END();

    public:
    virtual void setUp();
    virtual void tearDown();
    void testValidAsciiHexDigitData();
    void testInvalidAsciiHexDigitData();
    void testInvalidAsciiData();

    private:
    SMPP::Validation* pValidation_;

    static const unsigned char ValidAsciiHexDigitData[16];
    static const unsigned char InvalidAsciiHexDigitData[5];
    static const unsigned char InvalidAsciiData[5];
};

const unsigned char HexValidationTests::ValidAsciiHexDigitData[16] =
{
    0x30, 0x31, 0x32, 0x33, 0x34,
    0x35, 0x36, 0x37, 0x38, 0x39,
    0x41, 0x42, 0x43, 0x44, 0x45,
    0x46
};
const unsigned char HexValidationTests::InvalidAsciiHexDigitData[5] = { 0x40, 0x42, 0x35, 0x38, 0x39 };
const unsigned char HexValidationTests::InvalidAsciiData[5] = { 0x31, 0x55, 0x8F, 0x00, 0x90 };

CPPUNIT_TEST_SUITE_REGISTRATION(HexValidationTests);

void HexValidationTests::setUp()
{
    pValidation_ = new SMPP::HexValidation;
}

void HexValidationTests::tearDown()
{
    delete pValidation_;
}

void HexValidationTests::testValidAsciiHexDigitData()
{
    CPPUNIT_ASSERT_EQUAL(true, pValidation_->IsValid(&ValidAsciiHexDigitData[0], 16));
}

void HexValidationTests::testInvalidAsciiHexDigitData()
{
    CPPUNIT_ASSERT_EQUAL(false, pValidation_->IsValid(&InvalidAsciiHexDigitData[0], 5));
}

void HexValidationTests::testInvalidAsciiData()
{
    CPPUNIT_ASSERT_EQUAL(false, pValidation_->IsValid(&InvalidAsciiData[0], 5));
}

#endif // HEXVALIDATIONTESTS_H_
