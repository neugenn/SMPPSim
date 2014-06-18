#ifndef BINDTRANSMITTERTESTS_H_
#define BINDTRANSMITTERTESTS_H_

#include <cppunit/extensions/HelperMacros.h>
#include "BindTransmitter.h"

class TestingPduHeader : public PduHeader
{
public:
    TestingPduHeader() : PduHeader() {}

    virtual void GetFormattedContent(std::string& res) const
    {
        std::stringstream str;
        str << commandLen_;
        str << commandId_;
        str << commandStatus_;
        str << sequenceNum_;

        res = str.str();
    }
};

class TestingBindTransmitter : public SMPP::BindTransmitter
{
public:
    TestingBindTransmitter(PduHeader*& h) : SMPP::BindTransmitter(h)
    {
    }

    virtual void GetBodyInfo(std::string& s) const
    {
        std::stringstream str;
        str << systemId_;
        str << password_;
        str << systemType_;
        str << interfaceVersion_;
        str << addrTon_;
        str << addrNpi_;
        str << addressRange_;

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
    CPPUNIT_TEST(testCreateEmpty);
    CPPUNIT_TEST(testCommandId);
    CPPUNIT_TEST(testCommandIdFromValidData);
    CPPUNIT_TEST(testCommandIdFromInvalidValidData);
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
    void testCreateEmpty();
    void testCreateWithNULLData();
    void testCommandId();
    void testCommandIdFromValidData();
    void testCommandIdFromInvalidValidData();
    void testCopyConstructionNoCrash();
    void testAssignmentNoCrash();

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

void BindTransmitterTests::testCreateEmpty()
{
    PduHeader* ph = new TestingPduHeader;
    TestingBindTransmitter t(ph);
    std::stringstream s;
    s << t;
    CPPUNIT_ASSERT_EQUAL(std::string("0000000000000002000000000000000000000000000000"), s.str());
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

void BindTransmitterTests::testCopyConstructionNoCrash()
{
    {
        SMPP::BindTransmitter t1;
        SMPP::BindTransmitter t2(t1);
    }
    CPPUNIT_ASSERT(true);
}

void BindTransmitterTests::testAssignmentNoCrash()
{
    {
        SMPP::BindTransmitter t1;
        SMPP::BindTransmitter t2;
        t2 = t1;
    }
    CPPUNIT_ASSERT(true);
}

#endif // BINDTRANSMITTERTESTS_H_
