#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include <wirewalker/marshall.hpp>
#include <internal/oap/opcode.hpp>

namespace
{
    using namespace wirewalker;
    using namespace internal::oap;

    template <typename T>
    void marshallVerify(T const &val)
    {
        auto p = marshallSequence(val);
        auto um = Unmarshaller(p);
        auto readVal = unmarshall<T>(um);
        CPPUNIT_ASSERT(val == readVal);
    }

    class OpcodeMarshallTest: public CppUnit::TestFixture
    {
        CPPUNIT_TEST_SUITE(OpcodeMarshallTest);
        CPPUNIT_TEST(test_marshallMin);
        CPPUNIT_TEST(test_marshallMax);
        CPPUNIT_TEST_SUITE_END();

    public:
        void test_marshallMin();

        void test_marshallMax();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(OpcodeMarshallTest);

    void OpcodeMarshallTest::test_marshallMin()
    {
        auto opc = Opcode{Opcode::MIN};
        marshallVerify(opc);
    }

    void OpcodeMarshallTest::test_marshallMax()
    {
        auto opc = Opcode{Opcode::MAX};
        marshallVerify(opc);
    }
}
