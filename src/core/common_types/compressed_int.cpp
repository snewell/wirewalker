#include <wirewalker/compressed_int.hpp>

#include <wirewalker/marshall.hpp>

namespace wirewalker
{
    template <>
    Compressed16 const Compressed16::max = Compressed16{0x7FFF};

    template <>
    Compressed24 const Compressed24::max = Compressed24{0x3FFFFF};

    template <>
    Compressed32 const Compressed32::max = Compressed32{0x3FFFFFFF};

    template <>
    Size marshallSize<Compressed16>(Compressed16 const &val) noexcept
    {
        if(val < 0x80)
        {
            return 1;
        }
        return 2;
    }

    template <>
    void marshall<Compressed16>(Marshaller         &m,
                                Compressed16 const &val)
    {
        Byte buffer[2];
        auto index = 0u;
        if(val > 0x7F)
        {
            buffer[0] = ((val >> 8) & 0xFF) | 0x80;
            buffer[0] |= 0x80;
            ++index;
        }
        buffer[index++] = val & 0xFF;
        m.write(buffer, index);
    }

    template <>
    Compressed16 unmarshall<Compressed16>(Unmarshaller &um)
    {
        Compressed16::base_type val{0};
        Byte b;
        um.read(&b, 1);
        val |= (b & 0x7F);
        if(b & 0x80)
        {
            val <<= 8;
            um.read(&b, 1);
            val |= b;
        }
        return Compressed16{val};
    }

    template <>
    Size marshallSize<Compressed24>(Compressed24 const &val) noexcept
    {
        if(val < 0x80)
        {
            return 1;
        }
        else if(val < 0x4000)
        {
            return 2;
        }
        return 3;
    }

    template <>
    void marshall<Compressed24>(Marshaller         &m,
                                Compressed24 const &val)
    {
        Byte buffer[3];
        auto index = 0u;

        if(val > 0x3FFF)
        {
            buffer[index++] = ((val >> 16) & 0xFF) | 0xC0;
            buffer[index++] = (val >> 8) & 0xFF;
            buffer[index++] = val & 0xFF;
        }
        else if(val > 0x7F)
        {
            buffer[index++] = ((val >> 8) & 0xFF) | 0x80;
            buffer[index++] = val & 0xFF;
        }
        else
        {
            buffer[index++] = val & 0xFF;
        }
        m.write(buffer, index);
    }

    template <>
    Compressed24 unmarshall<Compressed24>(Unmarshaller &um)
    {
        Byte b;
        um.read(&b, 1);
        if(b & 0x80)
        {
            Compressed24::base_type val = b & 0x7F;
            val <<= 8;
            if(b & 0x40)
            {
                val &= 0x3FFF;
                um.read(&b, 1);
                val |= b;
                val <<= 8;
                um.read(&b, 1);
                val |= b;
                return Compressed24{val};
            }
            else
            {
                um.read(&b, 1);
                val |= b;
                return Compressed24{val};
            }
        }
        else
        {
            return Compressed24{b};
        }
    }

    template <>
    Size marshallSize<Compressed32>(Compressed32 const &val) noexcept
    {
        if(val < 0x80)
        {
            return 1;
        }
        else if(val < 0x4000)
        {
            return 2;
        }
        return 4;
    }

    template <>
    void marshall<Compressed32>(Marshaller         &m,
                                Compressed32 const &val)
    {
        Byte buffer[4];
        auto index = 0u;

        if(val > 0x3FFF)
        {
            buffer[index++] = ((val >> 24) & 0xFF) | 0xC0;
            buffer[index++] = (val >> 16) & 0xFF;
            buffer[index++] = (val >> 8) & 0xFF;
            buffer[index++] = val & 0xFF;
        }
        else if(val > 0x7F)
        {
            buffer[index++] = ((val >> 8) & 0xFF) | 0x80;
            buffer[index++] = val & 0xFF;
        }
        else
        {
            buffer[index++] = val & 0xFF;
        }
        m.write(buffer, index);
    }

    template <>
    Compressed32 unmarshall<Compressed32>(Unmarshaller &um)
    {
        Byte b;
        um.read(&b, 1);
        if(b & 0x80)
        {
            Compressed32::base_type val = b & 0x7F;
            val <<= 8;
            if(b & 0x40)
            {
                val &= 0x3FFF;
                um.read(&b, 1);
                val |= b;
                val <<= 8;
                um.read(&b, 1);
                val |= b;
                val <<= 8;
                um.read(&b, 1);
                val |= b;
                return Compressed32{val};
            }
            else
            {
                um.read(&b, 1);
                val |= b;
                return Compressed32{val};
            }
        }
        else
        {
            return Compressed32{b};
        }
    }
}
