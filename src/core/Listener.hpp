#pragma once
#include "Session.hpp"

#include <functional>
#include <memory>
#include <type_traits>

#include <net/socket.hpp>
#include <net/context.hpp>

class Listener
{
public:
    template<class SessionClass>
    requires std::is_base_of_v<Session, SessionClass>
    static std::unique_ptr<Listener> Open()
    {
        auto listener = std::unique_ptr<Listener>(new Listener);
        listener->_sessionFactory = []() {
            return std::make_shared<SessionClass>();
        };
        return std::move(listener);
    }
public:
    void Run(net::endpoint endpoint);
private:
    void OnAcceptCompleted(net::context*, bool);
private:
    Listener();
private:
    net::socket _sock;
    std::function<std::shared_ptr<Session>()> _sessionFactory;
};