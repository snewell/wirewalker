#include <wirewalker/packet.hpp>

using wirewalker::Marshaller;
using wirewalker::Unmarshaller;

Marshaller::Marshaller(Packet &packet,
                       Size    offset)
  : _packet{&packet},
    _offset{offset} { }

void Marshaller::write(Byte const * buffer,
                       Size         size)
{
    _packet->write(_offset, buffer, size);
    _offset += size;
}

Unmarshaller::Unmarshaller(Packet &packet,
                           Size    offset)
  : _packet{&packet},
    _offset{offset} { }

void Unmarshaller::read(Byte * buffer,
                        Size   size)
{
    _packet->read(_offset, buffer, size);
    _offset += size;
}
