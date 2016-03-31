#include <wirewalker/object_id.hpp>

#include <algorithm>

#include <wirewalker/marshall.hpp>

using wirewalker::ObjectId;

ObjectId::Builder::Builder(std::vector<Byte> data,
                           ObjectId::Class cls)
  : _data{std::move(data)},
    _dataOffset{_data.size()},
    _class{cls} { }

ObjectId::Builder ObjectId::Builder::email(std::string const &email)
{
    std::vector<Byte> data;
    data.resize(email.size());
    std::copy(std::begin(email), std::end(email), std::begin(data));
    return Builder{std::move(data), ObjectId::Class::EMAIL};
}

ObjectId ObjectId::Builder::build() const
{
    return ObjectId{_data, _class};
}
