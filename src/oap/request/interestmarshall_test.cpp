#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include <wirewalker/marshall.hpp>
#include <wirewalker/oap/request.hpp>

namespace
{
    using namespace wirewalker;
    using namespace wirewalker::oap;

    template <typename T>
    void marshallVerify(T const &val)
    {
        auto p = marshallSequence(val);
        auto um = Unmarshaller(p);
        auto readVal = unmarshall<T>(um);
        CPPUNIT_ASSERT(val == readVal);
    }

    class InterestRequestMarshallTest: public CppUnit::TestFixture
    {
        CPPUNIT_TEST_SUITE(InterestRequestMarshallTest);
        CPPUNIT_TEST(test_marshall_level<InterestRequest::Level::ACTIVATE>);
        CPPUNIT_TEST(test_marshall_level<InterestRequest::Level::CONNECT>);
        CPPUNIT_TEST(test_marshall_level<InterestRequest::Level::FULL_CONNECT>);
        CPPUNIT_TEST(test_marshall_level<InterestRequest::Level::WATCH>);
        CPPUNIT_TEST_SUITE_END();

    public:
        template <InterestRequest::Level LEVEL>
        void test_marshall_level();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(InterestRequestMarshallTest);

    template <InterestRequest::Level LEVEL>
    void InterestRequestMarshallTest::test_marshall_level()
    {
        auto request = InterestRequest{LEVEL, makePtr<InterfaceId>(InterfaceId::WILDCARD), makePtr<ObjectId>(ObjectId::BROADCAST)};
        marshallVerify(request);
    }
}
