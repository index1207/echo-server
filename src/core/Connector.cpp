#include "Connector.hpp"

#include <fmt/base.h>

Connector::Connector()
{
    _sock = std::make_unique<net::socket>(net::protocol::tcp);
}

void Connector::Run(net::endpoint endpoint)
{
    auto ctx = new net::context;
    ctx->endpoint = endpoint;
    ctx->completed = std::bind(&Connector::OnConnectCompleted, this, std::placeholders::_1, std::placeholders::_2);
    if (!_sock->connect(ctx))
        OnConnectCompleted(ctx, false);
}

void Connector::OnConnectCompleted(net::context* ctx, bool success)
{
    if (success)
    {
        auto session = _sessionFactory();
        session->Run(std::move(_sock));
    }
    else
    {
        fmt::println("Failed to connect with server.");
    }
    delete ctx;
}
