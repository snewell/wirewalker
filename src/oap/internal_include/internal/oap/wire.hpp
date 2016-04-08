#ifndef INTERNAL_OAP_WIRE_HPP
#define INTERNAL_OAP_WIRE_HPP 1

#include <wirewalker/packet.hpp>
#include <wirewalker/oap/request.hpp>

namespace internal
{
    namespace oap
    {
        void receive(wirewalker::Packet packet);

        wirewalker::Packet send(wirewalker::oap::InterestRequest const &request);
    }
}

#endif
