#pragma once
#include <Session.hpp>

#include <functional>
#include <type_traits>

#include <net/context.hpp>

class Connector
{
public:
    template<class SessionType> requires std::is_base_of_v<Session, SessionType>
    static std::unique_ptr<Connector> Open()
    {
        auto connector = new Connector;
        connector->_sessionFactory = []() {
            return std::make_shared<SessionType>();
        };
        return std::unique_ptr<Connector>(connector);
    }
public:
    void Run(net::endpoint endpoint);
private:
    void OnConnectCompleted(net::context* ctx, bool);
private:
    Connector();
private:
    net::socket _sock;
    std::function<std::shared_ptr<Session>()> _sessionFactory;
};