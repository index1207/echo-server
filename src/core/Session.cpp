#include "Session.hpp"

#include <fmt/base.h>

Session::Session() : _buffer {0,} {}
Session::~Session() = default;

void Session::Run(const std::shared_ptr<net::socket>& sock)
{
    _thisPtr = shared_from_this();
    _sock = sock;

    _recvCtx.set_buffer(_buffer);
    _recvCtx.completed = [&](net::context* ctx, bool success) {
        OnReceiveCompleted(ctx, success);
    };
    _sendCtx.completed = [&](net::context* ctx, bool success) {
        OnSendCompleted(ctx, success);
    };

    if (!_sock->receive(&_recvCtx))
        OnReceiveCompleted(&_recvCtx, false);

    OnConnected(_sock->get_remote_endpoint().value());
}

void Session::Send(std::span<char> data)
{
    std::lock_guard lock(_mtx);
    _sendCtx.set_buffer(data);
    if (!_sock->send(&_sendCtx))
        OnSendCompleted(&_sendCtx, false);
}

void Session::OnReceiveCompleted(net::context* ctx, bool success)
{
    if (!success || ctx->length == 0)
    {
        OnDisconnected(_sock->get_remote_endpoint().value());
        _thisPtr = nullptr;
        return;
    }
    OnReceived(_buffer, ctx->length);
    if (!_sock->receive(ctx))
        OnReceiveCompleted(ctx, false);
}

void Session::OnSendCompleted(net::context* ctx, bool success)
{
    if (success)
    {
        OnSent(ctx->length);
    }
}
