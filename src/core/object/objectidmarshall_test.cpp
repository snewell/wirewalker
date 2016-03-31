#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include <wirewalker/marshall.hpp>
#include <wirewalker/object_id.hpp>

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

    class ObjectIdMarshallTest: public CppUnit::TestFixture
    {
        CPPUNIT_TEST_SUITE(ObjectIdMarshallTest);
        CPPUNIT_TEST(test_marshallEmail);
        CPPUNIT_TEST_SUITE_END();

    public:
        void test_marshallEmail();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(ObjectIdMarshallTest);

    void ObjectIdMarshallTest::test_marshallEmail()
    {
        auto oid = ObjectId::Builder::email("test@test.com").build();
        marshallVerify(oid);
    }
}
