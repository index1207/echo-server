#include "Connector.hpp"

#include <net/dns.hpp>

#include <fmt/core.h>

class EchoSession : public Session
{
public:
    void OnConnected(net::endpoint endpoint) override
    {
        fmt::println("Connected {}", endpoint.to_string());

        char buffer[1024];
        memset(buffer, 'A', sizeof(buffer));

        Send(buffer);
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
        fmt::println("Sent {} bytes.", length);
    }
};

int main()
{
    net::native::initialize();
    auto endpoint = net::endpoint(net::dns::get_host_entry(net::dns::get_host_name()).address_list[0], 8888);
    auto listener = Connector::Open<EchoSession>();
    listener->Run(endpoint);

    getchar();
}