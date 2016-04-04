#include <internal/oap/opcode.hpp>

#include <wirewalker/marshall.hpp>

using internal::oap::Opcode;

Opcode::Opcode(std::uint8_t value)
  : _value{value}
{
}

std::uint8_t Opcode::getOpcode() const noexcept
{
    return _value & MAX;
}

namespace wirewalker
{
    template <>
    Size marshallSize<Opcode>(Opcode const &opc) noexcept
    {
        return 1;
    }

    template <>
    void marshall<Opcode>(Marshaller       &m,
                          Opcode     const &opc)
    {
        marshall(m, opc.getValue());
    }

    template <>
    Opcode unmarshall<Opcode>(Unmarshaller &um)
    {
        auto val = unmarshall<std::uint8_t>(um);
        return Opcode{val};
    }
}
