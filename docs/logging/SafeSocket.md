File: logging/inc/SafeSocket.hpp

Purpose
- Small RAII wrapper for POSIX sockets supporting move semantics.

Public API
- SafeSocket(int domain, int type, int protocol)
- ~SafeSocket()
- SafeSocket(SafeSocket&&)
- SafeSocket& operator=(SafeSocket&&)
- ssize_t send(const void* buf, size_t len, int flags)
- ssize_t receive(void* buf, size_t len, int flags)
- bool is_open() const
- void bind(const sockaddr* addr, socklen_t len)
- void listen(int backlog = SOMAXCONN)
- SafeSocket accept()  // commented in implementation
- int getFd()
- void connect(const sockaddr* addr, socklen_t len)

Key behavior
- Wraps socket(), connect(), bind(), listen() and provides safe close in destructor.
- Move-only type to ensure single ownership of the file descriptor.

Related files
- logging/src/SafeSocket.cpp
- logging/src/SocketTelemetrySrc.cpp
