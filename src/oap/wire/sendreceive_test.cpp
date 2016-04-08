#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include <internal/oap/wire.hpp>

namespace
{
    using namespace wirewalker;
    using namespace wirewalker::oap;

    class SendRecieveTest: public CppUnit::TestFixture
    {
        CPPUNIT_TEST_SUITE(SendRecieveTest);
        CPPUNIT_TEST(test_sendReceive_Interest<InterestRequest::Level::ACTIVATE>);
        CPPUNIT_TEST(test_sendReceive_Interest<InterestRequest::Level::CONNECT>);
        CPPUNIT_TEST(test_sendReceive_Interest<InterestRequest::Level::FULL_CONNECT>);
        CPPUNIT_TEST(test_sendReceive_Interest<InterestRequest::Level::WATCH>);
        CPPUNIT_TEST_SUITE_END();

    public:
        template <InterestRequest::Level LEVEL>
        void test_sendReceive_Interest();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(SendRecieveTest);

    template <InterestRequest::Level LEVEL>
    void SendRecieveTest::test_sendReceive_Interest()
    {
        auto request = InterestRequest{LEVEL, makePtr<InterfaceId>(InterfaceId::WILDCARD), makePtr<ObjectId>(ObjectId::BROADCAST)};
        auto p = internal::oap::send(request);
        internal::oap::receive(p);
    }
}
