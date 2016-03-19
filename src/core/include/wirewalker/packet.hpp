#ifndef WIREWALKER_PACKET_HPP
#define WIREWALKER_PACKET_HPP 1

#include <vector>

#include <wirewalker/types.hpp>

namespace wirewalker
{
    class Packet
    {
    public:
        Packet(Size size);

        Size getSize() const noexcept;

        void read(Size   offset,
                  Byte * buffer,
                  Size   amount) const;

        void write(Size         offset,
                   Byte const * buffer,
                   Size         amount);

    private:
        std::vector<Byte> _data;
    };

    class Marshaller
    {
    public:
        Marshaller(Packet &packet,
                   Size    offset = 0);

        Size getOffset() const noexcept;

        void write(Byte const * buffer,
                   Size         size);

    private:
        Packet * _packet;
        Size _offset;
    };

    class Unmarshaller
    {
    public:
        Unmarshaller(Packet &packet,
                     Size    offset = 0);

        Size getOffset() const noexcept;

        void read(Byte * buffer,
                  Size   size);

    private:
        Packet * _packet;
        Size _offset;
    };

    inline Size Packet::getSize() const noexcept
    {
        return _data.size();
    }

    inline Size Marshaller::getOffset() const noexcept
    {
        return _offset;
    }

    inline Size Unmarshaller::getOffset() const noexcept
    {
        return _offset;
    }
}

#endif
