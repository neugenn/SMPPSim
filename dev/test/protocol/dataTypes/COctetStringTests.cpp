#ifndef COCTETSTRINGTESTS_H_
#define COCTETSTRINGTESTS_H_

#include "AsciiValidation.h"
#include "COctetString.h"
#include "COctetString.cpp"

#include <cppunit/extensions/HelperMacros.h>
#include "Validation.h"

template <bool T>
class TestingValidation : public SMPP::Validation
{
public:
    TestingValidation()
    {}

    virtual bool IsValid(const unsigned char* /*data*/, size_t /*size*/) const
    {
        return T;
    }
};

template <bool T>
class TestingCOctetString : public SMPP::COctetString<TestingValidation<T> >
{
public:
   TestingCOctetString(const unsigned char* data, size_t len) : SMPP::COctetString<TestingValidation<T> >(data, len)
   {}
};

class COctetStringTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(COctetStringTests);
    CPPUNIT_TEST(testValidityWithValidationFailure);
    CPPUNIT_TEST(testValidityWithValidationOk);
    CPPUNIT_TEST(testCreateWithNullDataBuffer);
    CPPUNIT_TEST(testCreateWithSpecificSize);
    CPPUNIT_TEST(testEmptyStringSize);
    CPPUNIT_TEST(testEmptyStringData);
    CPPUNIT_TEST(testFormattedData);
    CPPUNIT_TEST(testSize);
    CPPUNIT_TEST_SUITE_END();

    public:
    virtual void setUp();
    virtual void tearDown();
    void testValidityWithValidationFailure();
    void testValidityWithValidationOk();
    void testCreateWithNullDataBuffer();
    void testCreateWithSpecificSize();
    void testEmptyStringSize();
    void testEmptyStringData();
    void testFormattedData();
    void testSize();

    private:
    TestingCOctetString<true>* pString_;

    public:
    static const unsigned char AsciiData[5];
};

CPPUNIT_TEST_SUITE_REGISTRATION(COctetStringTests);

const unsigned char COctetStringTests::AsciiData[5] = { 0x31, 0x32, 0x61, 0x41, 0x42 };

void COctetStringTests::setUp()
{
    const unsigned char* data = &AsciiData[0];
    pString_ = new TestingCOctetString<true>(data, 5);
    CPPUNIT_ASSERT(NULL != pString_);
}

void COctetStringTests::tearDown()
{
    delete pString_;
}

void COctetStringTests::testValidityWithValidationFailure()
{
    TestingCOctetString<false> s(&COctetStringTests::AsciiData[0], 5);
    CPPUNIT_ASSERT_EQUAL(false, s.IsValid());
}

void COctetStringTests::testValidityWithValidationOk()
{
    TestingCOctetString<true> s(&COctetStringTests::AsciiData[0], 5);
    CPPUNIT_ASSERT_EQUAL(true, s.IsValid());
}

void COctetStringTests::testCreateWithNullDataBuffer()
{
    const unsigned char* data = NULL;
    CPPUNIT_ASSERT_THROW(SMPP::CString(data, 1), std::invalid_argument);
}

void COctetStringTests::testCreateWithSpecificSize()
{
    const unsigned char* data = &AsciiData[0];
    SMPP::CString cs(data, 3);
    std::stringstream s;
    s << cs;
    CPPUNIT_ASSERT_EQUAL(std::string("313200"), s.str());
}

void COctetStringTests::testEmptyStringSize()
{
    SMPP::CString s;
    CPPUNIT_ASSERT_EQUAL(size_t(1), s.Size());
}

void COctetStringTests::testEmptyStringData()
{
    SMPP::CString s;
    std::stringstream r;
    r << s;
    CPPUNIT_ASSERT_EQUAL(std::string("00"), r.str());
}

void COctetStringTests::testFormattedData()
{
    std::stringstream s;
    s << *pString_;
    CPPUNIT_ASSERT_EQUAL(std::string("3132614100"), s.str());
}

void COctetStringTests::testSize()
{
    CPPUNIT_ASSERT_EQUAL(size_t(5), pString_->Size());
}

#endif // COCTETSTRINGTESTS_H_
