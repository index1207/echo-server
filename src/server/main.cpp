#include "Listener.hpp"

#include <fmt/core.h>

class EchoSession : public Session
{
public:
    void OnConnected(net::endpoint endpoint) override
    {
        fmt::println("Connected {}", endpoint.to_string());
    }

    void OnDisconnected(net::endpoint endpoint) override
    {
        fmt::println("Disconnected {}", endpoint.to_string());
    }

    void OnReceived(std::span<char> buffer, unsigned length) override
    {
        fmt::println("RECV {}", length);
    }

    void OnSent(unsigned length) override
    {

    }
};

int main()
{
    net::native::initialize();
    auto listener = Listener::Open<EchoSession>();
    listener->Run(net::endpoint(net::ip_address::loopback, 8888));

    getchar();
}