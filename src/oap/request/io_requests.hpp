#ifndef LOCAL_REQUESTS_HPP
#define LOCAL_REQUESTS_HPP 1

#include <wirewalker/interface_id.hpp>
#include <wirewalker/object_id.hpp>

#include <internal/oap/opcode.hpp>

namespace internal
{
    namespace request
    {
        struct Request
        {
            internal::oap::Opcode opcode;
        };

        struct BindingRequest
        {
            Request req;
            wirewalker::Ptr<wirewalker::InterfaceId> iid;
            wirewalker::Ptr<wirewalker::ObjectId> oid;
        };
    }
}

#endif
