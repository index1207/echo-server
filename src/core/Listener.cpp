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
            throw net::network_exception("bind()");

        if (!_sock.listen())
            throw net::network_exception("listen");

        auto ctx = new net::context;
        ctx->completed = std::bind(&Listener::OnAcceptCompleted, this, std::placeholders::_1, std::placeholders::_2);
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
        session->Run(std::move(ctx->accept_socket));

        ctx->accept_socket = std::make_unique<net::socket>();
        if (!_sock.accept(ctx))
            OnAcceptCompleted(ctx, false);
    }
    else
    {
        fmt::println("Accept Failed.");
    }
}
