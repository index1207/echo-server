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

        std::string data;
        std::cin >> data;
        Send(data);
    }

    void OnDisconnected(net::endpoint endpoint) override
    {
        fmt::println("Disconnected with {}", endpoint.to_string());
    }

    void OnReceived(std::span<char> buffer, unsigned length) override
    {
        fmt::println("Received {} bytes", length);

        std::string data;
        std::cin >> data;
        Send(data);
    }

    void OnSent(unsigned length) override
    {
        fmt::println("Sent {} bytes", length);
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