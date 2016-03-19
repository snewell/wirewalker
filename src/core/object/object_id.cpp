#include <wirewalker/object_id.hpp>

#include <wirewalker/marshall.hpp>

namespace wirewalker
{
    template <>
    Size marshallSize<ObjectId>(ObjectId const &oid) noexcept
    {
        return 0;
    }
}
