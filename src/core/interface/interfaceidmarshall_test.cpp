#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include <wirewalker/marshall.hpp>
#include <wirewalker/interface_id.hpp>

namespace
{
    using namespace wirewalker;

    template <typename T>
    void marshallVerify(T const &val)
    {
        auto p = marshallSequence(val);
        auto um = Unmarshaller(p);
        auto readVal = unmarshall<T>(um);
        CPPUNIT_ASSERT(val == readVal);
    }

    class InterfaceIdMarshallTest: public CppUnit::TestFixture
    {
        CPPUNIT_TEST_SUITE(InterfaceIdMarshallTest);
        CPPUNIT_TEST(test_marshall_1);
        CPPUNIT_TEST(test_marshall_2);
        CPPUNIT_TEST(test_marshall_4);
        CPPUNIT_TEST_SUITE_END();

    public:
        void test_marshall_1();

        void test_marshall_2();

        void test_marshall_4();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(InterfaceIdMarshallTest);

    void InterfaceIdMarshallTest::test_marshall_1()
    {
        std::vector<Byte> data = { 0x00 };
        auto iid = InterfaceId{0, std::move(data)};
        marshallVerify(iid);
    }

    void InterfaceIdMarshallTest::test_marshall_2()
    {
        std::vector<Byte> data = { 0x00, 0x00 };
        auto iid = InterfaceId{0, std::move(data)};
        marshallVerify(iid);
    }

    void InterfaceIdMarshallTest::test_marshall_4()
    {
        std::vector<Byte> data = { 0x00, 0x00, 0x00, 0x00 };
        auto iid = InterfaceId{0, std::move(data)};
        marshallVerify(iid);
    }
}
