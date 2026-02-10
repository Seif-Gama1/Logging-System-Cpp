#pragma once

#include "ITelemetrySrc.hpp"
#include "SafeSocket.hpp"
#include <string>
#include <cstdint>

class SocketTelemetrySrc : public ITelemetrySrc {
private:
    SafeSocket socket;
    std::string ip;
    uint16_t port;

public:
    SocketTelemetrySrc(const std::string& ipAddr,
                       uint16_t port,
                       int domain = AF_INET,
                       int type = SOCK_STREAM,
                       int protocol = 0);

    SocketTelemetrySrc(const SocketTelemetrySrc& other) = delete;
    SocketTelemetrySrc& operator=(const SocketTelemetrySrc& other) = delete;

    SocketTelemetrySrc(SocketTelemetrySrc&& other);
    SocketTelemetrySrc& operator=(SocketTelemetrySrc&& other);

    bool openSource() override;
    bool readSource(std::string& out) override;
    std::string sourcePath() const override;
};
