#ifndef WIREWALKER_TYPES_HPP
#define WIREWALKER_TYPES_HPP 1

#include <cstdint>
#include <memory>

namespace wirewalker
{
    using Byte = std::uint8_t;

    using Size = std::size_t;

    template <typename T>
    using Ptr = std::shared_ptr<T>;

    template <typename T>
    using ConstPtr = Ptr<T const>;

    template <typename T, typename ...Ts>
    auto makePtr(Ts && ...ts)
    {
        return std::make_shared<T>(std::forward<Ts...>(ts...));
    }
}

#endif
