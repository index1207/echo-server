#pragma once

#include <memory>

#include <net/socket.hpp>
#include <net/context.hpp>

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session();
    virtual ~Session();
public:
    void Run(const net::socket& sock);

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
    net::context _recvCtx;
    net::context _sendCtx;
    std::shared_ptr<Session> _thisPtr;
    net::socket _sock;
    char _buffer[0x10000];
};
