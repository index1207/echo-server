#include "Listener.hpp"

#include <net/dns.hpp>

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
        fmt::println("Receive {} bytes.", length);
        Send(buffer.subspan(0, length));
    }

    void OnSent(unsigned length) override
    {
        fmt::println("Sent {}", length);
    }
};

int main()
{
    net::native::initialize();
    auto endpoint = net::endpoint(net::dns::get_host_entry(net::dns::get_host_name()).address_list[0], 8888);
    auto listener = Listener::Open<EchoSession>();
    listener->Run(endpoint);

    fmt::println("Server is running on {}", endpoint.to_string());

    getchar();
}