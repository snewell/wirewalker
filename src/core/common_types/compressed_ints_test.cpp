#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include <wirewalker/compressed_int.hpp>
#include <wirewalker/marshall.hpp>

#define COMMA ,

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
    class CompressedIntTest: public CppUnit::TestFixture
    {
        CPPUNIT_TEST_SUITE(CompressedIntTest<T>);
        CPPUNIT_TEST(test_marshall0);
        CPPUNIT_TEST(test_marshallMax);
        CPPUNIT_TEST_SUITE_END();

    public:
        void test_marshall0();

        void test_marshallMax();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(CompressedIntTest<Compressed16>);
    CPPUNIT_TEST_SUITE_REGISTRATION(CompressedIntTest<Compressed24>);
    CPPUNIT_TEST_SUITE_REGISTRATION(CompressedIntTest<Compressed32>);

    template <typename T>
    void CompressedIntTest<T>::test_marshall0()
    {
        auto const val = T{0};
        auto size = marshallSize(val);
        CPPUNIT_ASSERT_EQUAL(Size{1}, size);
        marshallVerify(val);
    }

    template <typename T>
    void CompressedIntTest<T>::test_marshallMax()
    {
        auto size = marshallSize(T::max);
        CPPUNIT_ASSERT_EQUAL(T::byte_size(), size);
        marshallVerify(T::max);
    }

    class CompressedIntEdgeCasesTest : public CppUnit::TestFixture
    {
        CPPUNIT_TEST_SUITE(CompressedIntEdgeCasesTest);
        CPPUNIT_TEST(test_edgeCase<Compressed16 COMMA 0x7F COMMA 1>);
        CPPUNIT_TEST(test_edgeCase<Compressed16 COMMA 0x80 COMMA 2>);

        CPPUNIT_TEST(test_edgeCase<Compressed24 COMMA 0x7F COMMA 1>);
        CPPUNIT_TEST(test_edgeCase<Compressed24 COMMA 0x80 COMMA 2>);
        CPPUNIT_TEST(test_edgeCase<Compressed24 COMMA 0x3FFF COMMA 2>);
        CPPUNIT_TEST(test_edgeCase<Compressed24 COMMA 0x4000 COMMA 3>);

        CPPUNIT_TEST(test_edgeCase<Compressed32 COMMA 0x7F COMMA 1>);
        CPPUNIT_TEST(test_edgeCase<Compressed32 COMMA 0x80 COMMA 2>);
        CPPUNIT_TEST(test_edgeCase<Compressed32 COMMA 0x3FFF COMMA 2>);
        CPPUNIT_TEST(test_edgeCase<Compressed32 COMMA 0x4000 COMMA 4>);
        CPPUNIT_TEST_SUITE_END();

    public:
        template <typename T, std::uint32_t VALUE, std::size_t SIZE>
        void test_edgeCase();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(CompressedIntEdgeCasesTest);

    template <typename T, std::uint32_t VALUE, std::size_t SIZE>
    void CompressedIntEdgeCasesTest::test_edgeCase()
    {
        auto const val = T{VALUE};
        auto size = marshallSize(val);
        CPPUNIT_ASSERT_EQUAL(SIZE, size);
        marshallVerify(val);
    }
}
