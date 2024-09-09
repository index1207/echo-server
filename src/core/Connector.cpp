#include "Connector.hpp"

#include <fmt/base.h>

Connector::Connector()
{
    _sock = std::make_shared<net::socket>(net::protocol::tcp);
}

void Connector::Run(net::endpoint endpoint)
{
    auto ctx = new net::context;
    ctx->endpoint = endpoint;
    ctx->completed = [&](net::context* ctx, bool success) {
        OnConnectCompleted(ctx, success);
    };
    if (!_sock->connect(ctx))
        OnConnectCompleted(ctx, false);
}

void Connector::OnConnectCompleted(net::context* ctx, bool success)
{
    if (success)
    {
        auto session = _sessionFactory();
        session->Run(_sock);
    }
    else
    {
        fmt::println("Failed to connect with server.");
    }
    delete ctx;
}
