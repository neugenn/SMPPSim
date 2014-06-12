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

    virtual bool IsValid(const unsigned char* /*data*/, size_t /*size*/)
    {
        return T;
    }
};

template <bool T>
class TestingCOctetString : public SMPP::COctetString<TestingValidation<T> >
{
public:
   TestingCOctetString(const unsigned char* data) : SMPP::COctetString<TestingValidation<T> >(data)
   {}
};

class COctetStringTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(COctetStringTests);
    CPPUNIT_TEST(testCreateWithValidationFailure);
    CPPUNIT_TEST(testCreateWithNULLDataBuffer);
    CPPUNIT_TEST(testEmptyStringSize);
    CPPUNIT_TEST(testEmptyStringData);
    CPPUNIT_TEST(testFormattedData);
    CPPUNIT_TEST(testSize);
    CPPUNIT_TEST_SUITE_END();

    public:
    virtual void setUp();
    virtual void tearDown();
    void testCreateWithValidationFailure();
    void testCreateWithNULLDataBuffer();
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

const unsigned char COctetStringTests::AsciiData[5] = { 0x31, 0x32, 0x61, 0x41, 0x00 };

void COctetStringTests::setUp()
{
    pString_ = new TestingCOctetString<true>(&AsciiData[0]);
    CPPUNIT_ASSERT(NULL != pString_);
}

void COctetStringTests::tearDown()
{
    delete pString_;
}

void COctetStringTests::testCreateWithValidationFailure()
{
    CPPUNIT_ASSERT_THROW(new TestingCOctetString<false>(&COctetStringTests::AsciiData[0]), std::invalid_argument);
}

void COctetStringTests::testCreateWithNULLDataBuffer()
{
    CPPUNIT_ASSERT_THROW(SMPP::CString(NULL), std::invalid_argument);
}

void COctetStringTests::testEmptyStringSize()
{
    SMPP::CString s;
    CPPUNIT_ASSERT_EQUAL(size_t(1), s.Size());
}

void COctetStringTests::testEmptyStringData()
{
    SMPP::CString s;
    std::string r;
    SMPP::PduDataType::GetFormattedData(s.Data(), s.Size(), r);
    CPPUNIT_ASSERT_EQUAL(std::string("00"), r);
}

void COctetStringTests::testFormattedData()
{
    std::string r;
    SMPP::PduDataType::GetFormattedData(pString_->Data(), pString_->Size(), r);
    CPPUNIT_ASSERT_EQUAL(std::string("3132614100"), r);
}

void COctetStringTests::testSize()
{
    CPPUNIT_ASSERT_EQUAL(size_t(5), pString_->Size());
}

#endif // COCTETSTRINGTESTS_H_
