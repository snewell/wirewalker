#include <wirewalker/oap/request.hpp>

#include <wirewalker/marshall.hpp>

#include "io_requests.hpp"

using wirewalker::oap::Request;
using wirewalker::oap::BindingRequest;

Request::Request(Type type)
  : _type{type} { }

BindingRequest::BindingRequest(Type             type,
                               Ptr<InterfaceId> iid,
                               Ptr<ObjectId>    oid)
 : Request{type},
   _interfaceId{std::move(iid)},
   _objectId{std::move(oid)} { }

namespace wirewalker
{
    template <>
    Size marshallSize<internal::request::Request>(internal::request::Request const &req) noexcept
    {
        return marshallSize(req.opcode);
    }

    template <>
    Size marshallSize<internal::request::BindingRequest>(internal::request::BindingRequest const &req) noexcept
    {
        return marshallSize(req.req) +
               marshallSize(*(req.iid)) +
               marshallSize(*(req.oid));
    }

    template <>
    void marshall<internal::request::Request>(Marshaller                       &m,
                                              internal::request::Request const &req)
    {
        marshall(m, req.opcode);
    }

    template <>
    void marshall<internal::request::BindingRequest>(Marshaller                              &m,
                                                     internal::request::BindingRequest const &req)
    {
        marshall(m, req.req, *(req.iid), *(req.oid));
    }

    template <>
    internal::request::Request unmarshall<internal::request::Request>(Unmarshaller &um)
    {
        auto opc = unmarshall<internal::oap::Opcode>(um);
        return internal::request::Request{opc};
    }

    template <>
    internal::request::BindingRequest unmarshall<internal::request::BindingRequest>(Unmarshaller &um)
    {
        auto req = unmarshall<internal::request::Request>(um);
        auto iid = unmarshall<InterfaceId>(um);
        auto oid = unmarshall<ObjectId>(um);
        return internal::request::BindingRequest{std::move(req), makePtr<InterfaceId>(std::move(iid)),
                                                 makePtr<ObjectId>(std::move(oid))};
    }
}
