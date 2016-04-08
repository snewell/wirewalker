#include <internal/oap/wire.hpp>

#include <wirewalker/marshall.hpp>

#include <wirewalker/oap/request.hpp>
#include <internal/oap/opcode.hpp>

namespace
{
    void receiveInterest(wirewalker::Unmarshaller &um)
    {
        auto op = wirewalker::unmarshall<wirewalker::oap::InterestRequest>(um);
    }
}

namespace internal
{
    namespace oap
    {
        void receive(wirewalker::Packet packet)
        {
            wirewalker::Unmarshaller um{packet};

            auto offset = um.getOffset();
            auto opc = wirewalker::unmarshall<internal::oap::Opcode>(um);
            um.setOffset(offset);
            switch(opc.getOpcode())
            {
            case internal::oap::Opcode::ACTIVATE:
            case internal::oap::Opcode::CONNECT:
            case internal::oap::Opcode::FULL_CONNECT:
            case internal::oap::Opcode::WATCH:
                receiveInterest(um);
                break;
            }
        }
    }
}
