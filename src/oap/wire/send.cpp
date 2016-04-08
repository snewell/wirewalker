#include <internal/oap/wire.hpp>

#include <wirewalker/marshall.hpp>

namespace internal
{
    namespace oap
    {
        wirewalker::Packet send(wirewalker::oap::InterestRequest const &request)
        {
            return wirewalker::marshallSequence(request);
        }
    }
}
