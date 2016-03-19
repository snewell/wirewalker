#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
#include <boost/concept_check.hpp>

#include <string>

#include <wirewalker/packet.hpp>

namespace
{
    using namespace wirewalker;

    class PacketTest : public CppUnit::TestFixture
    {
        CPPUNIT_TEST_SUITE(PacketTest);
        CPPUNIT_TEST(test_ctor);
        CPPUNIT_TEST(test_writeMessage);
        CPPUNIT_TEST(test_writeMessageOffset);
        CPPUNIT_TEST_SUITE_END();

    public:
        void test_ctor();

        void test_writeMessage();

        void test_writeMessageOffset();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(PacketTest);

    void PacketTest::test_ctor()
    {
        auto const size = Size{10};
        auto p = Packet{size};
        CPPUNIT_ASSERT_EQUAL(size, p.getSize());
    }

    void PacketTest::test_writeMessage()
    {
        auto const rawData = std::string{"Hello, world"};
        auto p = Packet{rawData.size()};
        p.write(0, (Byte *) rawData.data(), rawData.size());
    }

    void PacketTest::test_writeMessageOffset()
    {
        auto const rawData = std::string{"Hello, world"};
        auto p = Packet{rawData.size() + 10};
        p.write(5, (Byte *) rawData.data(), rawData.size());
    }
}
