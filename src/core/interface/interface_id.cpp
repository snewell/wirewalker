#include <wirewalker/interface_id.hpp>

#include <stdexcept>

#include <wirewalker/marshall.hpp>

using wirewalker::InterfaceId;

namespace
{
    void verifyIdRegistry(std::uint8_t registry)
    {
        if(registry > 0x3F)
        {
            throw std::runtime_error{"Invalid InterfaceId registry"};
        }
    }

    // this is the wire size for the data
    std::uint8_t verifyIdData(std::vector<wirewalker::Byte> const &data)
    {
        switch(data.size())
        {
        case 1:
            return 1;
            break;

        case 2:
            return 2;
            break;

        case 4:
            return 3;
            break;

        default:
            throw std::runtime_error{"Invalid InterfaceId size"};
        }
    }
}

InterfaceId::InterfaceId(std::uint8_t                  registry,
                         std::vector<wirewalker::Byte> data)
  : _data{std::move(data)},
    _registry{registry}
{
    verifyIdRegistry(_registry);
    verifyIdData(_data);
}


namespace wirewalker
{
    bool operator == (InterfaceId const &lhs,
                      InterfaceId const &rhs) noexcept
    {
        if(lhs.getRegistry() == rhs.getRegistry())
        {
            if(lhs.getData().size() == rhs.getData().size())
            {
                return std::equal(std::begin(lhs.getData()), std::end(lhs.getData()),
                                  std::begin(rhs.getData()));
            }
        }
        return false;
    }

    template <>
    Size marshallSize<InterfaceId>(InterfaceId const &id) noexcept
    {
        return 1 + id.getData().size();
    }

    template <>
    void marshall<InterfaceId>(Marshaller        &m,
                               InterfaceId const &id)
    {
        auto firstByte = std::uint8_t{id.getRegistry()};
        firstByte <<= 2;
        firstByte |= verifyIdData(id.getData());
        marshall(m, firstByte);
        m.write(id.getData().data(), id.getData().size());
    }

    template <>
    InterfaceId unmarshall<InterfaceId>(Unmarshaller &um)
    {
        static Size const dataSizes[4] = { 0, 1, 2, 4 };
        auto firstByte = unmarshall<std::uint8_t>(um);
        auto localSize = dataSizes[firstByte & 0x03];
        std::vector<Byte> data;
        data.resize(localSize);
        um.read(data.data(), localSize);
        return InterfaceId{static_cast<std::uint8_t>(firstByte >> 2), std::move(data)};
    }
}
