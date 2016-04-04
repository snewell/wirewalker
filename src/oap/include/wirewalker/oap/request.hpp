#ifndef WIREWALKER_OAP_REQUEST_HPP
#define WIREWALKER_OAP_REQUEST_HPP 1

#include <wirewalker/interface_id.hpp>
#include <wirewalker/object_id.hpp>

namespace wirewalker
{
    namespace oap
    {
        class Request
        {
        public:
            enum class Type
            {
                INTEREST,
                LAST
            };

            Request(Type type);

            Type getType() const noexcept;

        private:
            Type _type;
        };

        class BindingRequest : public Request
        {
        public:
            BindingRequest(Type             type,
                           Ptr<InterfaceId> iid,
                           Ptr<ObjectId>    oid);

            Ptr<InterfaceId> const& getInterfaceId() const noexcept;

            Ptr<ObjectId> const& getObjectId() const noexcept;

        private:
            Ptr<InterfaceId> _interfaceId;
            Ptr<ObjectId> _objectId;
        };

        class InterestRequest : public BindingRequest
        {
        public:
            enum class Level
            {
                ACTIVATE,
                CONNECT,
                FULL_CONNECT,
                WATCH
            };

            InterestRequest(Level            level,
                            Ptr<InterfaceId> interfaceId,
                            Ptr<ObjectId>    objectId);

            Level getLevel() const noexcept;

        private:
            Level _level;
        };

        bool operator == (InterestRequest const &lhs,
                          InterestRequest const &rhs);

        inline Request::Type Request::getType() const noexcept
        {
            return _type;
        }

        inline Ptr<InterfaceId> const& BindingRequest::getInterfaceId() const noexcept
        {
            return _interfaceId;
        }

        inline Ptr<ObjectId> const& BindingRequest::getObjectId() const noexcept
        {
            return _objectId;
        }

        inline InterestRequest::Level InterestRequest::getLevel() const noexcept
        {
            return _level;
        }
    }
}

#endif
