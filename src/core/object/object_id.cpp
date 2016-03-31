#include <wirewalker/object_id.hpp>

#include <algorithm>

#include <wirewalker/compressed_int.hpp>
#include <wirewalker/marshall.hpp>

using wirewalker::ObjectId;

ObjectId::ObjectId(std::vector<Byte> data,
                   Class             cls)
  : _data{std::move(data)},
    _class{cls}
{
}

#define MAKE_OID_CLASS_CASE(val)    case static_cast<std::uint32_t>(ObjectId::Class::val):     \
                                        return ObjectId::Class::val;                           \
                                        break

namespace
{
    auto makeCompressedClass(ObjectId::Class cls)
    {
        return wirewalker::Compressed32{static_cast<wirewalker::Compressed32::base_type>(cls)};
    }
}

namespace wirewalker
{
    bool operator == (ObjectId const &lhs,
                      ObjectId const &rhs)
    {
        return (lhs.getClass() == rhs.getClass()) &&
               std::equal(std::begin(lhs.getData()), std::end(lhs.getData()), std::begin(rhs.getData()));
    }

    template <>
    Size marshallSize<ObjectId::Class>(ObjectId::Class const &cls) noexcept
    {
        return marshallSize(makeCompressedClass(cls));
    }

    template <>
    void marshall<ObjectId::Class>(Marshaller            &m,
                                   ObjectId::Class const &cls)
    {
        marshall(m, makeCompressedClass(cls));
    }

    template <>
    ObjectId::Class unmarshall<ObjectId::Class>(Unmarshaller &um)
    {
        auto raw = unmarshall<Compressed32>(um);
        switch(raw)
        {
            MAKE_OID_CLASS_CASE(EMAIL);
        }
    }

    template <>
    Size marshallSize<ObjectId>(ObjectId const &oid) noexcept
    {
        // size of the id plus a byte for data size
        auto ret = marshallSize(oid.getClass()) + 1;
        ret += oid.getData().size();
        // TODO: attributes
        return ret;
    }

    template <>
    void marshall<ObjectId>(Marshaller       &m,
                            ObjectId   const &oid)
    {
        auto const &data = oid.getData();
        std::uint8_t sizeByte = data.size();
        // TODO: check for attributes
        marshall(m, oid.getClass(), sizeByte);
        m.write(data.data(), data.size());
        // TODO: write attributes
    }

    template <>
    ObjectId unmarshall<ObjectId>(Unmarshaller &um)
    {
        auto cls = unmarshall<ObjectId::Class>(um);
        auto size = unmarshall<std::uint8_t>(um);
        size &= 0x7F;       // TODO: handle attributes
        std::vector<Byte> data;
        data.resize(size);
        std::for_each(std::begin(data), std::end(data), [&um](auto &v) {
            v = unmarshall<Byte>(um);
        });
        return ObjectId{std::move(data), cls};
    }
}
