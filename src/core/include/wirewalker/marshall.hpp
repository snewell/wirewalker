#ifndef WIREWALKER_MARSHALL_HPP
#define WIREWALKER_MARSHALL_HPP 1

#include <wirewalker/packet.hpp>
#include <wirewalker/types.hpp>

namespace wirewalker
{
    template <typename T>
    Size marshallSize(T const &t) noexcept;

    template <typename T, typename ...Ts>
    Size marshallSize(T const &t,
                      Ts && ...ts) noexcept
    {
        return marshallSize(t) + marshallSize(ts...);
    }

    template <typename T>
    void marshall(Marshaller       &m,
                  T          const &t);

    template <typename T, typename ...Ts>
    void marshall(Marshaller       &m,
                  T          const &t,
                  Ts               && ...ts)
    {
        marshall(m, t);
        marshall(m, ts...);
    }

    template <typename ...Ts>
    Packet marshall(Ts && ...ts)
    {
        auto fullSize = marshallSize(ts...);
        auto ret = Packet{fullSize};
        auto marshaller = Marshaller{ret};
        marshall(marshaller, ts...);
        return ret;
    }

    template <typename T>
    T unmarshall(Unmarshaller &um);
}

#endif
