#ifndef BINDTRANSMITTERTESTS_H_
#define BINDTRANSMITTERTESTS_H_

#include <cppunit/extensions/HelperMacros.h>
#include "BindTransmitter.h"

class BindTransmitterTests : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(BindTransmitterTests);
    CPPUNIT_TEST(testCreateWithNULLData);
    CPPUNIT_TEST(testCommandId);
    CPPUNIT_TEST(testCommandIdFromValidData);
    CPPUNIT_TEST(testCommandIdFromInvalidValidData);
    CPPUNIT_TEST_SUITE_END();

	public:
	virtual void setUp();
	virtual void tearDown();
    void testCreateWithNULLData();
    void testCommandId();
    void testCommandIdFromValidData();
    void testCommandIdFromInvalidValidData();

    private:
    SMPP::BindTransmitter* pPdu_;

    public:
    static const unsigned char ValidBindTransmitterData[20];
    static const unsigned char InvalidBindTransmitterData[20];
};

const unsigned char BindTransmitterTests::ValidBindTransmitterData[20] = {
    0x00, 0x00, 0x00, 0x02, // command_length
    0x00, 0x00, 0x00, 0x02, // command_id
    0x31, 0x32, 0x33, 0x34, // command_status
    0x00, 0x00, 0x00, 0x01, // sequence_number
    0x00, 0x00, 0x00, 0x01
};

const unsigned char BindTransmitterTests::InvalidBindTransmitterData[20] = {
    0x00, 0x00, 0x00, 0x02, // command_length
    0x00, 0x10, 0x00, 0x02, // command_id (invalid)
    0x31, 0x32, 0x33, 0x34, // command_status
    0x00, 0x00, 0x00, 0x01, // sequence_number
    0x00, 0x00, 0x00, 0x01
};

CPPUNIT_TEST_SUITE_REGISTRATION(BindTransmitterTests);

void BindTransmitterTests::setUp()
{
    pPdu_ = new SMPP::BindTransmitter(&ValidBindTransmitterData[0], 20);
    CPPUNIT_ASSERT(NULL != pPdu_);
}

void BindTransmitterTests::tearDown()
{
    delete pPdu_;
}

void BindTransmitterTests::testCreateWithNULLData()
{
    CPPUNIT_ASSERT_THROW(new SMPP::BindTransmitter(NULL, 10), std::invalid_argument);
}

void BindTransmitterTests::testCommandId()
{
    SMPP::BindTransmitter t;
    const uint32_t id = t.GetHeader().GetCommandId();
    CPPUNIT_ASSERT_EQUAL(uint32_t(0x00000002), id);
}

void BindTransmitterTests::testCommandIdFromValidData()
{
    SMPP::BindTransmitter t(&ValidBindTransmitterData[0], 20);
    const uint32_t id = t.GetHeader().GetCommandId();
    CPPUNIT_ASSERT_EQUAL(uint32_t(0x00000002), id);
}

void BindTransmitterTests::testCommandIdFromInvalidValidData()
{
    CPPUNIT_ASSERT_THROW(new SMPP::BindTransmitter(&InvalidBindTransmitterData[0], 20), std::invalid_argument);
}

#endif // BINDTRANSMITTERTESTS_H_
