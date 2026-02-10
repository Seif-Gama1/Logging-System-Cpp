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
    if (sockfd != -1) {
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

void SafeSocket::bind(const sockaddr* addr, socklen_t len){
    if (::bind(sockfd, addr, len) < 0) {
        throw std::system_error(errno, std::system_category(), "bind");
    }
}

void SafeSocket::listen(int backlog){
    if (::listen(sockfd, backlog) < 0) {
        throw std::system_error(errno, std::system_category(), "listen");
    }
}

// SafeSocket SafeSocket::accept(){
//     int fd = ::accept(sockfd, nullptr, nullptr);
//     if (fd < 0) {
//         throw std::system_error(errno, std::system_category(), "accept");
//     }
//     return SafeSocket(fd); # need a proper CTOR of 3 parameters here, or maybe a default CTOR
// }

void SafeSocket::connect(const sockaddr* addr, socklen_t len){
    if (::connect(sockfd, addr, len) < 0) {
        throw std::system_error(errno, std::system_category(), "connect");
    }
}

int SafeSocket::getFd(){
    return sockfd;
}