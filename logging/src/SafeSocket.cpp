#include "SafeSocket.hpp"
#include <iostream>

SafeSocket::SafeSocket(int domain, int type, int protocol) {
    sockfd = ::socket(domain, type, protocol);
    if (sockfd == -1) {
        std::cout << "Error opening socket"<<std::endl; /* Testing */
    }
}

bool SafeSocket::is_open() const {
    if(sockfd != -1) return true;
    return false;
}


SafeSocket::~SafeSocket() {
    if (sockfd != -1) {
        close(sockfd);
        sockfd = -1;
    }
}

SafeSocket::SafeSocket(SafeSocket&& other)
    : sockfd(other.sockfd)
{
    other.sockfd = -1;
}

SafeSocket& SafeSocket::operator=(SafeSocket&& other){
    if (this != &other) {
        if (sockfd != -1) {
            close(sockfd);
        }
        sockfd = other.sockfd;
        other.sockfd = -1;
    }
    return *this;
}

ssize_t SafeSocket::send(const void* buf, size_t len, int flags) {
    if (sockfd == -1) {
        return ::send(sockfd, buf, len, flags);
    }
    throw std::runtime_error("Send on closed socket");
    // return -1;
}

ssize_t SafeSocket::receive(void* buf, size_t len, int flags) {
    if (sockfd != -1) {
        return recv(sockfd, buf, len, flags);
    }
    throw std::runtime_error("Receive on closed socket");
    // return -1;
}
