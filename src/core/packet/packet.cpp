#include <wirewalker/packet.hpp>

#include <algorithm>
#include <stdexcept>

using wirewalker::Packet;

Packet::Packet(Size size)
  : _data(size) { }

void Packet::read(Size   offset,
                  Byte * buffer,
                  Size   amount) const
{
    validate(offset, amount);
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
    validate(offset, amount);
    auto start = std::begin(_data);
    std::advance(start, offset);
    std::copy(buffer, buffer + amount, start);
}

void Packet::validate(Size offset,
                      Size amount) const
{
    if(_data.size() < (offset + amount))
    {
        throw std::runtime_error{"Insufficient space in packet"};
    }
}
