#pragma once
#include <unistd.h>
#include <sys/socket.h>
#include <string>
#include <stdexcept>

class SafeSocket {
private:
    int sockfd{-1};

public:
    SafeSocket() = delete;
    SafeSocket(int domain, int type, int protocol);

    ~SafeSocket();

    // copy semantics
    SafeSocket(const SafeSocket& other) = delete;
    SafeSocket& operator=(const SafeSocket& other) = delete;

    // move semantics
    SafeSocket(SafeSocket&& other);
    SafeSocket& operator=(SafeSocket&& other);

    // APIs
    ssize_t send(const void* buf, size_t len, int flags);
    ssize_t receive(void* buf, size_t len, int flags);
    bool is_open() const;
    void bind(const sockaddr* addr, socklen_t len);
    void listen(int backlog = SOMAXCONN);
    SafeSocket accept();
    int getFd();
    void connect(const sockaddr* addr, socklen_t len);
};
