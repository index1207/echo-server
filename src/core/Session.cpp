#include "Session.hpp"

#include <fmt/base.h>
#include <net/context.hpp>

Session::Session() : _buffer {0,} {}
Session::~Session() = default;

void Session::Run(std::unique_ptr<net::socket>&& sock)
{
    _thisPtr = shared_from_this();
    _sock = std::move(sock);

    auto ctx = new net::context;
    ctx->buffer = _buffer;
    ctx->completed = std::bind(&Session::OnReceiveCompleted, this, std::placeholders::_1, std::placeholders::_2);
    if (!_sock->receive(ctx))
        OnReceiveCompleted(ctx, false);

    OnConnected(_sock->get_remote_endpoint().value());
}

void Session::Send(std::span<char> data)
{
    auto ctx = new net::context;
    ctx->buffer = data;
    ctx->completed = std::bind(&Session::OnSendCompleted, this, std::placeholders::_1, std::placeholders::_2);

    if (!_sock->send(ctx))
        OnSendCompleted(ctx, false);
}

void Session::OnReceiveCompleted(net::context* ctx, bool success)
{
    if (ctx->length == 0)
    {
        OnDisconnected(_sock->get_remote_endpoint().value());
        _thisPtr = nullptr;
    }
    else if (success)
    {
        OnReceived(ctx->buffer, ctx->length);
        if (!_sock->receive(ctx))
            OnReceiveCompleted(ctx, false);
    }
}

void Session::OnSendCompleted(net::context* ctx, bool success)
{
    if (success)
    {
        OnSent(ctx->length);
    }
    delete ctx;
}
