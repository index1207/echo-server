#include "Connector.hpp"

#include <iostream>
#include <thread>

#include <net/dns.hpp>

#include <fmt/core.h>

using namespace std::chrono_literals;

class EchoSession : public Session
{
public:
    void OnConnected(net::endpoint endpoint) override
    {
        fmt::println("Connected to {}", endpoint.to_string());

        char buffer[1024];
        memset(buffer, 'A', sizeof(buffer));

        Send(buffer);
    }

    void OnDisconnected(net::endpoint endpoint) override
    {
        fmt::println("Disconnected with {}", endpoint.to_string());
    }

    void OnReceived(std::span<char> buffer, unsigned length) override
    {
        Send(buffer.subspan(0, length));
    }

    void OnSent(unsigned length) override
    {
    }
};

int main()
{
    net::native::initialize();
    auto endpoint = net::endpoint(net::dns::get_host_entry(net::dns::get_host_name()).address_list[0], 8888);
    auto connector = Connector::Open<EchoSession>();
    connector->Run(endpoint);

    while (true)
    {
        std::this_thread::sleep_for(1s);
    }
}