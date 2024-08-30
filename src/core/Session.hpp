#pragma once

#include <memory>

#include <net/socket.hpp>

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session();
    virtual ~Session();
public:
    void Run(std::unique_ptr<net::socket>&& sock);

    void Send(std::span<char> data);
public:
    virtual void OnConnected(net::endpoint endpoint) = 0;
    virtual void OnDisconnected(net::endpoint endpoint) = 0;
    virtual void OnReceived(std::span<char> buffer, unsigned length) = 0;
    virtual void OnSent(unsigned length) = 0;
private:
    void OnReceiveCompleted(net::context*, bool);
    void OnSendCompleted(net::context*, bool);
private:
    std::shared_ptr<Session> _thisPtr;
    std::unique_ptr<net::socket> _sock;
    char _buffer[0x10000];
};
