#ifndef INTERNAL_OAP_OPCODE_HPP
#define INTERNAL_OAP_OPCODE_HPP 1

#include <cstdint>

namespace internal
{
    namespace oap
    {
        class Opcode
        {
        public:
            Opcode(std::uint8_t value);

            std::uint8_t getValue() const noexcept;

            std::uint8_t getOpcode() const noexcept;

            static std::uint8_t const MIN = 0x00;

            static std::uint8_t const MAX = 0x1F;

            static std::uint8_t const ACTIVATE = 0x1C;

            static std::uint8_t const CONNECT = 0x04;

            static std::uint8_t const FULL_CONNECT = 0x03;

            static std::uint8_t const WATCH = 0x1E;

        private:
            std::uint8_t _value;
        };

        inline bool operator == (Opcode const &lhs,
                                 Opcode const &rhs)
        {
            return (lhs.getValue() == rhs.getValue());
        }

        inline std::uint8_t Opcode::getValue() const noexcept
        {
            return _value;
        }
    }
}

#endif
