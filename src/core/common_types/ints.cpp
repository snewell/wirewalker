#include <wirewalker/marshall.hpp>

#include <cstring>

namespace
{
    template <typename UT, typename ST>
    auto marshallWrapper(ST s)
    {
        static_assert(sizeof(ST) == sizeof(UT), "Incompatible types");
        UT temp;
        std::memcpy(&temp, &s, sizeof(UT));
        return wirewalker::marshallSize(temp);
    }

    template <typename UT, typename ST>
    void marshallWrapper(wirewalker::Marshaller &m,
                         ST                      s)
    {
        static_assert(sizeof(ST) == sizeof(UT), "Incompatible types");
        UT temp;
        std::memcpy(&temp, &s, sizeof(UT));
        wirewalker::marshall(m, temp);
    }

    template <typename UT, typename ST>
    ST unmarshallWrapper(wirewalker::Unmarshaller &um)
    {
        static_assert(sizeof(ST) == sizeof(UT), "Incompatible types");
        auto temp = wirewalker::unmarshall<UT>(um);
        ST ret;
        std::memcpy(&ret, &temp, sizeof(UT));
        return ret;
    }

    template <typename T>
    void writeMultibyte(wirewalker::Marshaller &m,
                        T                       val)
    {
        wirewalker::Byte buffer[sizeof(T)];
        auto index = sizeof(T);
        while(index != 0)
        {
            buffer[--index] = val & 0xFF;
            val >>= 8;
        }
        m.write(buffer, sizeof(T));
    }

    template <typename T>
    T readMultibyte(wirewalker::Unmarshaller &um)
    {
        wirewalker::Byte buffer[sizeof(T)];
        um.read(buffer, sizeof(T));
        auto ret = T{0};
        for(auto i = 0u; i < sizeof(T); ++i)
        {
            ret <<= 8;
            ret |= buffer[i];
        }
        return ret;
    }
}

namespace wirewalker
{
    template <>
    Size marshallSize<std::uint8_t>(std::uint8_t const &) noexcept
    {
        return 1;
    }

    template <>
    void marshall<std::uint8_t>(Marshaller         &m,
                                std::uint8_t const &val)
    {
        m.write(&val, 1);
    }

    template <>
    std::uint8_t unmarshall<std::uint8_t>(Unmarshaller &um)
    {
        std::uint8_t ret;
        um.read(&ret, 1);
        return ret;
    }

    template <>
    Size marshallSize<std::uint16_t>(std::uint16_t const &) noexcept
    {
        return 2;
    }

    template <>
    void marshall<std::uint16_t>(Marshaller          &m,
                                 std::uint16_t const &val)
    {
        writeMultibyte(m, val);
    }

    template <>
    std::uint16_t unmarshall<std::uint16_t>(Unmarshaller &um)
    {
        return readMultibyte<std::uint16_t>(um);
    }

    template <>
    Size marshallSize<std::uint32_t>(std::uint32_t const &) noexcept
    {
        return 4;
    }

    template <>
    void marshall<std::uint32_t>(Marshaller          &m,
                                 std::uint32_t const &val)
    {
        writeMultibyte(m, val);
    }

    template <>
    std::uint32_t unmarshall<std::uint32_t>(Unmarshaller &um)
    {
        return readMultibyte<std::uint32_t>(um);
    }

    template <>
    Size marshallSize<std::uint64_t>(std::uint64_t const &) noexcept
    {
        return 8;
    }

    template <>
    void marshall<std::uint64_t>(Marshaller          &m,
                                 std::uint64_t const &val)
    {
        writeMultibyte(m, val);
    }

    template <>
    std::uint64_t unmarshall<std::uint64_t>(Unmarshaller &um)
    {
        return readMultibyte<std::uint64_t>(um);
    }

    template <>
    Size marshallSize<std::int8_t>(std::int8_t const &val) noexcept
    {
        return marshallWrapper<std::uint8_t>(val);
    }

    template <>
    void marshall<std::int8_t>(Marshaller        &m,
                               std::int8_t const &val)
    {
        marshallWrapper<std::uint8_t>(m, val);
    }

    template <>
    std::int8_t unmarshall<std::int8_t>(Unmarshaller &um)
    {
        return unmarshallWrapper<std::uint8_t, std::int8_t>(um);
    }

    template <>
    Size marshallSize<std::int16_t>(std::int16_t const &val) noexcept
    {
        return marshallWrapper<std::uint16_t>(val);
    }

    template <>
    void marshall<std::int16_t>(Marshaller         &m,
                                std::int16_t const &val)
    {
        marshallWrapper<std::uint16_t>(m, val);
    }

    template <>
    std::int16_t unmarshall<std::int16_t>(Unmarshaller &um)
    {
        return unmarshallWrapper<std::uint16_t, std::int16_t>(um);
    }

    template <>
    Size marshallSize<std::int32_t>(std::int32_t const &val) noexcept
    {
        return marshallWrapper<std::uint32_t>(val);
    }

    template <>
    void marshall<std::int32_t>(Marshaller         &m,
                                std::int32_t const &val)
    {
        marshallWrapper<std::uint32_t>(m, val);
    }

    template <>
    std::int32_t unmarshall<std::int32_t>(Unmarshaller &um)
    {
        return unmarshallWrapper<std::uint32_t, std::int32_t>(um);
    }

    template <>
    Size marshallSize<std::int64_t>(std::int64_t const &val) noexcept
    {
        return marshallWrapper<std::uint64_t>(val);
    }

    template <>
    void marshall<std::int64_t>(Marshaller         &m,
                                std::int64_t const &val)
    {
        marshallWrapper<std::uint64_t>(m, val);
    }

    template <>
    std::int64_t unmarshall<std::int64_t>(Unmarshaller &um)
    {
        return unmarshallWrapper<std::uint64_t, std::int64_t>(um);
    }
}
