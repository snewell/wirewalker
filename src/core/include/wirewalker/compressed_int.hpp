#ifndef WIREWALKER_COMPRESSED_INT_HPP
#define WIREWALKER_COMPRESSED_INT_HPP 1

#include <wirewalker/types.hpp>

namespace wirewalker
{
    template <typename BASE, Size BYTE_SIZE = sizeof(BASE)>
    class CompressedInt
    {
    public:
        using base_type = BASE;

        static Size constexpr byte_size() noexcept {return BYTE_SIZE; }

        static CompressedInt<BASE, BYTE_SIZE> const max;

        CompressedInt(BASE val = 0)
          : _val{val} { }

        operator BASE& () noexcept
        {
            return _val;
        }

        operator BASE const& () const noexcept
        {
            return _val;
        }

    private:
        BASE _val;
    };

    using Compressed16  = CompressedInt<std::uint16_t, 2>;
    using Compressed24  = CompressedInt<std::uint32_t, 3>;
    using Compressed32  = CompressedInt<std::uint32_t, 4>;
}

#endif
