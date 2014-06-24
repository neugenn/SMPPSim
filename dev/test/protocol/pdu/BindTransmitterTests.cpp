#ifndef BINDTRANSMITTERTESTS_H_
#define BINDTRANSMITTERTESTS_H_

#include <cppunit/extensions/HelperMacros.h>
#include <iomanip>
#include "BindTransmitter.h"

class TestingBindTransmitter : public SMPP::BindTransmitter
{
public:
    TestingBindTransmitter() : SMPP::BindTransmitter()
    {}

    virtual void GetFormattedContent(std::string& s) const
    {
        const size_t pduSize = this->Size();
        unsigned char* pdu = new unsigned char[pduSize];
        memcpy(pdu, this->Data(), pduSize);

        std::stringstream str;
        for (size_t i = 0; i < pduSize; ++i)
        {
            str << std::setfill('0') << std::setw(2) << std::uppercase << std::hex;
            str << static_cast<unsigned int>(pdu[i]);
        }
        delete [] pdu;

        s = str.str();
    }
};

class BindTransmitterTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(BindTransmitterTests);
    CPPUNIT_TEST(testSystemIdLen);
    CPPUNIT_TEST(testPasswordLen);
    CPPUNIT_TEST(testSystemTypeLen);
    CPPUNIT_TEST(testAddressRangeLen);
    CPPUNIT_TEST(testMinPduSize);
    CPPUNIT_TEST(testMaxPduSize);
    CPPUNIT_TEST(testCreateEmpty);
    CPPUNIT_TEST(testCreateWithNullData);
    CPPUNIT_TEST(testCreateWithShortCommandLen);
    CPPUNIT_TEST(testCreateWithLongCommandLen);
    CPPUNIT_TEST(testCreateWithInvalidCommandId);
    CPPUNIT_TEST(testCommandId);
    CPPUNIT_TEST(testCommandIdFromValidData);
    CPPUNIT_TEST(testCopyConstructionNoCrash);
    CPPUNIT_TEST(testAssignmentNoCrash);
    CPPUNIT_TEST_SUITE_END();

	public:
	virtual void setUp();
    virtual void tearDown();
    void testSystemIdLen();
    void testPasswordLen();
    void testSystemTypeLen();
    void testAddressRangeLen();
    void testMinPduSize();
    void testMaxPduSize();
    void testCreateEmpty();
    void testCreateWithNullData();
    void testCommandId();
    void testCommandIdFromValidData();
    void testCreateWithInvalidCommandId();
    void testCreateWithShortCommandLen();
    void testCreateWithLongCommandLen();
    void testCopyConstructionNoCrash();
    void testAssignmentNoCrash();

    private:
    SMPP::BindTransmitter* pPdu_;

    public:
    static const unsigned char ValidBindTransmitterData[33];
};

const unsigned char BindTransmitterTests::ValidBindTransmitterData[33] =
{
    0x00, 0x00, 0x00, 0x21, // command_length
    0x00, 0x00, 0x00, 0x02, // command_id
    0x00, 0x00, 0x00, 0x00, // command_status
    0x00, 0x00, 0x00, 0x01, // sequence_number
    0x73, 0x6d, 0x73, 0x00,  // system_id
    0x70, 0x61, 0x31, 0x00, // password
    0x4f, 0x54, 0x41, 0x00, // system_type
    0x34, // interface_version
    0x01, // addr_ton
    0x01, // addr_npi
    0x01, 0x00 // address_range
};


CPPUNIT_TEST_SUITE_REGISTRATION(BindTransmitterTests);

void BindTransmitterTests::setUp()
{
    pPdu_ = new SMPP::BindTransmitter(&ValidBindTransmitterData[0]);
    CPPUNIT_ASSERT(NULL != pPdu_);
}

void BindTransmitterTests::tearDown()
{
//    delete pPdu_;
}

void BindTransmitterTests::testSystemIdLen()
{
    CPPUNIT_ASSERT_EQUAL(size_t(16), SMPP::BindTransmitter::SystemIdMaxLen);
}

void BindTransmitterTests::testPasswordLen()
{
    CPPUNIT_ASSERT_EQUAL(size_t(9), SMPP::BindTransmitter::PasswordMaxLen);
}

void BindTransmitterTests::testSystemTypeLen()
{
    CPPUNIT_ASSERT_EQUAL(size_t(13), SMPP::BindTransmitter::SystemTypeMaxLen);
}

void BindTransmitterTests::testAddressRangeLen()
{
    CPPUNIT_ASSERT_EQUAL(size_t(41), SMPP::BindTransmitter::AddressRangeMaxLen);
}

void BindTransmitterTests::testMinPduSize()
{
    SMPP::BindTransmitter t;
    CPPUNIT_ASSERT_EQUAL(size_t(23), t.MinSize());
}

void BindTransmitterTests::testMaxPduSize()
{
    SMPP::BindTransmitter t;
    CPPUNIT_ASSERT_EQUAL(size_t(98), t.MaxSize());
}

void BindTransmitterTests::testCreateEmpty()
{
    TestingBindTransmitter t;

    std::stringstream s;
    s << t;
    CPPUNIT_ASSERT_EQUAL(std::string("0000001700000002000000000000000000000000000000"), s.str());
}

void BindTransmitterTests::testCreateWithNullData()
{
    CPPUNIT_ASSERT_THROW(new SMPP::BindTransmitter(NULL), std::invalid_argument);
}

void BindTransmitterTests::testCommandId()
{
    SMPP::BindTransmitter t;
    CPPUNIT_ASSERT_EQUAL(SMPP::BIND_TRANSMITTER, t.CommandId());
}

void BindTransmitterTests::testCommandIdFromValidData()
{
    SMPP::BindTransmitter t(&ValidBindTransmitterData[0]);
    CPPUNIT_ASSERT_EQUAL(SMPP::BIND_TRANSMITTER, t.CommandId());
}

void BindTransmitterTests::testCreateWithInvalidCommandId()
{
    const unsigned char InvalidCommandIdData[] =
    {
        0x00, 0x00, 0x00, 0x20, // command_length
        0x00, 0x00, 0x00, 0x03, // command_id (invalid)
        0x00, 0x00, 0x00, 0x00, // command_status
        0x00, 0x00, 0x00, 0x01, // sequence_number
        0x73, 0x6d, 0x73, 0x00,  // system_id
        0x70, 0x61, 0x31, 0x00, // password
        0x4f, 0x54, 0x41, 0x00, // system_type
        0x34, // interface_version
        0x01, // addr_ton
        0x01, // addr_npi
        0x01, 0x00 // address_range
        };

    CPPUNIT_ASSERT_THROW(new SMPP::BindTransmitter(&InvalidCommandIdData[0]), std::invalid_argument);
}

void BindTransmitterTests::testCreateWithShortCommandLen()
{
    const unsigned char InvalidShortCommandLenData[] =
    {
        0x00, 0x00, 0x00, 0x01, // command_length
        0x00, 0x00, 0x00, 0x02, // command_id
        0x00, 0x00, 0x00, 0x00, // command_status
        0x00, 0x00, 0x00, 0x01, // sequence_number
        0x73, 0x6d, 0x73, 0x00,  // system_id
        0x70, 0x61, 0x31, 0x00, // password
        0x4f, 0x54, 0x41, 0x00, // system_type
        0x34, // interface_version
        0x01, // addr_ton
        0x01, // addr_npi
        0x01, 0x00 // address_range
        };

    CPPUNIT_ASSERT_THROW(new SMPP::BindTransmitter(&InvalidShortCommandLenData[0]), std::invalid_argument);
}

void BindTransmitterTests::testCreateWithLongCommandLen()
{
    const unsigned char InvalidLongCommandLenData[] =
    {
        0x00, 0x00, 0x00, 0xFF, // command_length
        0x00, 0x00, 0x00, 0x02, // command_id
        0x00, 0x00, 0x00, 0x00, // command_status
        0x00, 0x00, 0x00, 0x01, // sequence_number
        0x73, 0x6d, 0x73, 0x00,  // system_id
        0x70, 0x61, 0x31, 0x00, // password
        0x4f, 0x54, 0x41, 0x00, // system_type
        0x34, // interface_version
        0x01, // addr_ton
        0x01, // addr_npi
        0x01, 0x00 // address_range
        };

    CPPUNIT_ASSERT_THROW(new SMPP::BindTransmitter(&InvalidLongCommandLenData[0]), std::invalid_argument);
}

void BindTransmitterTests::testCopyConstructionNoCrash()
{
    {
        SMPP::BindTransmitter t1;
        SMPP::BindTransmitter t2(t1);

        t1.CommandId();
        t2.CommandId();
    }
    CPPUNIT_ASSERT(true);
}

void BindTransmitterTests::testAssignmentNoCrash()
{
    {
        SMPP::BindTransmitter t1;
        SMPP::BindTransmitter t2;
        t2 = t1;

        t1.CommandId();
        t2.CommandId();
    }
    CPPUNIT_ASSERT(true);
}
#endif // BINDTRANSMITTERTESTS_H_
