#include "Listener.hpp"

#include <net/dns.hpp>

#include <fmt/core.h>

std::string d = "h";

class EchoSession : public Session
{
public:
    void OnConnected(net::endpoint endpoint) override
    {
        fmt::println("Connected to {}", endpoint.to_string());
    }

    void OnDisconnected(net::endpoint endpoint) override
    {
        fmt::println("Disconnected with {}", endpoint.to_string());
    }

    void OnReceived(std::span<char> buffer, unsigned length) override
    {
        Send(d);
    }

    void OnSent(unsigned length) override
    {
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