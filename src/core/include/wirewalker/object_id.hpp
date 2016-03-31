#ifndef WIREWALKER_OBJECT_ID_HPP
#define WIREWALKER_OBJECT_ID_HPP 1

#include <string>
#include <vector>

#include <wirewalker/types.hpp>

namespace wirewalker
{
    class ObjectId
    {
    public:
        enum class Class
        {
            MAC48 = 0x02,
            EMAIL = 0x03
        };

        ObjectId(std::vector<Byte> data,
                 Class             cls);

        Class getClass() const noexcept;

        std::vector<Byte> const& getData() const noexcept;

        class Builder
        {
        public:
            static Builder email(std::string const &email);

            ObjectId build() const;

        private:
            Builder(std::vector<Byte> data,
                    ObjectId::Class cls);

            std::vector<Byte> _data;
            std::vector<Byte>::size_type const _dataOffset;

            ObjectId::Class _class;
        };

    private:
        std::vector<Byte> _data;
        Class _class;
    };

    inline ObjectId::Class ObjectId::getClass() const noexcept
    {
        return _class;
    }

    inline std::vector<Byte> const& ObjectId::getData() const noexcept
    {
        return _data;
    }

    bool operator == (ObjectId const &lhs,
                      ObjectId const &rhs);
}

#endif
