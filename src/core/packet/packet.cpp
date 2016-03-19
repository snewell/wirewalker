#include <wirewalker/packet.hpp>

#include <algorithm>

using wirewalker::Packet;

Packet::Packet(Size size)
  : _data(size) { }

void Packet::read(Size   offset,
                  Byte * buffer,
                  Size   amount) const
{
    auto start = std::begin(_data);
    std::advance(start, offset);
    auto end = start;
    std::advance(end, amount);
    std::copy(start, end, buffer);
}

void Packet::write(Size         offset,
                   Byte const * buffer,
                   Size         amount)
{
    auto start = std::begin(_data);
    std::advance(start, offset);
    std::copy(buffer, buffer + amount, start);
}
