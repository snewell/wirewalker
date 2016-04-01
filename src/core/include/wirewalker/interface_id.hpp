#ifndef WIREWALKER_INTERFACE_ID_HPP
#define WIREWALKER_INTERFACE_ID_HPP 1

#include <vector>

#include <wirewalker/types.hpp>

namespace wirewalker
{
    class InterfaceId
    {
    public:
        InterfaceId(std::uint8_t      registry,
                    std::vector<Byte> data);

        std::uint8_t getRegistry() const noexcept;

        std::vector<Byte> const& getData() const noexcept;

    private:
        std::vector<Byte> _data;
        std::uint8_t _registry;
    };

    bool operator == (InterfaceId const &lhs,
                      InterfaceId const &rhs) noexcept;

    inline std::uint8_t InterfaceId::getRegistry() const noexcept
    {
        return _registry;
    }

    inline std::vector<Byte> const& InterfaceId::getData() const noexcept
    {
        return _data;
    }
}

#endif
