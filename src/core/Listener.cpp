#include "Listener.hpp"

#include <net/context.hpp>
#include <net/exception.hpp>

#include <fmt/core.h>

Listener::Listener()
{
    _sock.create(net::protocol::tcp);
}

void Listener::Run(net::endpoint endpoint)
{
    try
    {
        if (!_sock.bind(endpoint))
            throw net::exception("bind()");

        if (!_sock.listen())
            throw net::exception("listen");

        auto ctx = new net::context;
        ctx->completed = [&](net::context* ctx, bool success) {
            OnAcceptCompleted(ctx, success);
        };
        if (!_sock.accept(ctx))
            OnAcceptCompleted(ctx, false);
    }
    catch (std::exception& e)
    {
        fmt::println("{}", e.what());
    }
}

void Listener::OnAcceptCompleted(net::context* ctx, bool success)
{
    if (success)
    {
        auto session = _sessionFactory();
        session->Run(ctx->accept_socket);
    }
    else
    {
        fmt::println("Accept Failed.");
    }
    if (!_sock.accept(ctx))
        OnAcceptCompleted(ctx, false);
}
