#include <wirewalker/oap/request.hpp>

#include <wirewalker/marshall.hpp>

#include "io_requests.hpp"

using wirewalker::oap::InterestRequest;

InterestRequest::InterestRequest(Level            level,
                                 Ptr<InterfaceId> interfaceId,
                                 Ptr<ObjectId>    objectId)
  : BindingRequest{Request::Type::INTEREST, std::move(interfaceId), std::move(objectId)},
    _level{level} { }

namespace
{
    auto makeOpcode(InterestRequest::Level level) noexcept
    {
        switch(level)
        {
        case InterestRequest::Level::ACTIVATE:
            return internal::oap::Opcode{internal::oap::Opcode::ACTIVATE};
            break;

        case InterestRequest::Level::CONNECT:
            return internal::oap::Opcode{internal::oap::Opcode::CONNECT};
            break;

        case InterestRequest::Level::FULL_CONNECT:
            return internal::oap::Opcode{internal::oap::Opcode::FULL_CONNECT};
            break;

        case InterestRequest::Level::WATCH:
            return internal::oap::Opcode{internal::oap::Opcode::WATCH};
            break;
        }
    }

    auto makeRequest(InterestRequest const &req)
    {
        return internal::request::BindingRequest{makeOpcode(req.getLevel()), req.getInterfaceId(), req.getObjectId()};
    }
}

namespace wirewalker
{
    namespace oap
    {
        bool operator == (InterestRequest const &lhs,
                          InterestRequest const &rhs)
        {
            return (lhs.getLevel() == rhs.getLevel());
        }
    }

    template <>
    Size marshallSize<InterestRequest>(InterestRequest const &req) noexcept
    {
        return marshallSize(makeRequest(req));
    }

    template <>
    void marshall<InterestRequest>(Marshaller            &m,
                                   InterestRequest const &req)
    {
        marshall(m, makeRequest(req));
    }

    template <>
    InterestRequest unmarshall<InterestRequest>(Unmarshaller &um)
    {
        auto req = unmarshall<internal::request::BindingRequest>(um);
        switch(req.req.opcode.getOpcode())
        {
        case internal::oap::Opcode::ACTIVATE:
            return InterestRequest{InterestRequest::Level::ACTIVATE, std::move(req.iid), std::move(req.oid)};
            break;

        case internal::oap::Opcode::CONNECT:
            return InterestRequest{InterestRequest::Level::CONNECT, std::move(req.iid), std::move(req.oid)};
            break;

        case internal::oap::Opcode::FULL_CONNECT:
            return InterestRequest{InterestRequest::Level::FULL_CONNECT, std::move(req.iid), std::move(req.oid)};
            break;

        case internal::oap::Opcode::WATCH:
            return InterestRequest{InterestRequest::Level::WATCH, std::move(req.iid), std::move(req.oid)};
            break;
        }
    }
}
