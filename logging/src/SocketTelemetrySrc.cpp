#include "SocketTelemetrySrc.hpp"
#include <arpa/inet.h>
#include <cstring>

SocketTelemetrySrc::SocketTelemetrySrc(const std::string& ipAddr,
                                       uint16_t port,
                                       int domain,
                                       int type,
                                       int protocol)
    : socket(domain, type, protocol),
      ip(ipAddr),
      port(port) {}

SocketTelemetrySrc::SocketTelemetrySrc(SocketTelemetrySrc&& other)
    : socket(std::move(other.socket)),
      ip(std::move(other.ip)),
      port(other.port) {}

SocketTelemetrySrc& SocketTelemetrySrc::operator=(SocketTelemetrySrc&& other) {
    if (this != &other) {
        socket = std::move(other.socket);
        ip = std::move(other.ip);
        port = other.port;
    }
    return *this;
}

bool SocketTelemetrySrc::openSource() {
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (::inet_pton(AF_INET, ip.c_str(), &addr.sin_addr) <= 0) {
        return false;
    }

    return ::connect(socket.getFd(),
                     reinterpret_cast<sockaddr*>(&addr),
                     sizeof(addr)) == 0;
}

bool SocketTelemetrySrc::readSource(std::string& out) {
    char buffer[256];
    ssize_t bytesRead = socket.receive(buffer, sizeof(buffer) - 1, 0);

    if (bytesRead <= 0) {
        return false;
    }

    buffer[bytesRead] = '\0';
    out.assign(buffer);
    return true;
}

std::string SocketTelemetrySrc::sourcePath() const {
    return ip + ":" + std::to_string(port);
}
