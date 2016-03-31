#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include <limits>

#include <wirewalker/marshall.hpp>

namespace
{
    using namespace wirewalker;

    template <typename T>
    void marshallVerify(T const &val)
    {
        auto p = marshallSequence(val);
        auto um = Unmarshaller(p);
        auto readVal = unmarshall<T>(um);
        CPPUNIT_ASSERT_EQUAL(val, readVal);
    }

    template <typename T>
    class IntsTest: public CppUnit::TestFixture
    {
        CPPUNIT_TEST_SUITE(IntsTest<T>);
        CPPUNIT_TEST(test_marshallMin);
        CPPUNIT_TEST(test_marshallZero);
        CPPUNIT_TEST(test_marshallMax);
        CPPUNIT_TEST_SUITE_END();

    public:
        void test_marshallMin();

        void test_marshallZero();

        void test_marshallMax();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(IntsTest<std::int8_t>);
    CPPUNIT_TEST_SUITE_REGISTRATION(IntsTest<std::uint8_t>);
    CPPUNIT_TEST_SUITE_REGISTRATION(IntsTest<std::int16_t>);
    CPPUNIT_TEST_SUITE_REGISTRATION(IntsTest<std::uint16_t>);
    CPPUNIT_TEST_SUITE_REGISTRATION(IntsTest<std::int32_t>);
    CPPUNIT_TEST_SUITE_REGISTRATION(IntsTest<std::uint32_t>);
    CPPUNIT_TEST_SUITE_REGISTRATION(IntsTest<std::int64_t>);
    CPPUNIT_TEST_SUITE_REGISTRATION(IntsTest<std::uint64_t>);

    template <typename T>
    void IntsTest<T>::test_marshallMin()
    {
        auto const val = std::numeric_limits<T>::min();
        auto size = marshallSize(val);
        CPPUNIT_ASSERT_EQUAL(Size{sizeof(T)}, size);
        marshallVerify(val);
    }

    template <typename T>
    void IntsTest<T>::test_marshallZero()
    {
        auto const val = T{0};
        auto size = marshallSize(val);
        CPPUNIT_ASSERT_EQUAL(Size{sizeof(T)}, size);
        marshallVerify(val);
    }

    template <typename T>
    void IntsTest<T>::test_marshallMax()
    {
        auto const val = std::numeric_limits<T>::max();
        auto size = marshallSize(val);
        CPPUNIT_ASSERT_EQUAL(Size{sizeof(T)}, size);
        marshallVerify(val);
    }
}
