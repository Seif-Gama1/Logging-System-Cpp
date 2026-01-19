#pragma once
#include "LogMessage.hpp"

class ITelemetrySrc{
    public:
        virtual ~ITelemetrySrc() = default;
        
        virtual bool openSource() = 0;
        virtual bool readSource(std::string& out) = 0;
        virtual std::string sourcePath() const = 0;
};

// openSource() : bool → responsible for openning source/establishing connection.
// readSource(out : string&) : bool → reads the source and stores the latest reading in out.

// 1. At least one of these RAII-compliant classes: SafeFile & SafeSocket.
// - SafeFile wraps POSIX file operations into a safe environment that guarantees reliable source management.
//   Only move semantics should be implemented and copy semantics should be removed. Hint: look up <unistd.h>. (done)
// - SafeSocket wraps standard Unix Domain Socket operations into a safe environment that guarantees reliable
//   source management. Only move semantics should be implemented and copy semantics should be removed. Hint: look up <unistd.h>. (done)
// 2. At least one of the following Rule-of-Zero-compliant classes (only std components and RAII-compliant ones should be used):
// - FileTelemetrySourceImpl class that implements ITelemetrySource and utilizes SafeFile class. The source should a shell script that simply writes float numbers into a file (will be provided).
// - SocketTelemetrySourceImpl class that implements ITelemetrySource and utilizes SafeSocket class.

// 3. Refactor LogMessage to default all special member functions. (done)