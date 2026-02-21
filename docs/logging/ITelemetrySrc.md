File: logging/inc/ITelemetrySrc.hpp

Purpose
- Abstract interface for telemetry sources (file, socket, SOME/IP client, etc.). Defines the minimal contract used by the app to read telemetry values.

Public API
- class ITelemetrySrc
  - virtual ~ITelemetrySrc()
  - virtual bool openSource() = 0
  - virtual bool readSource(std::string& out) = 0
  - virtual std::string sourcePath() const = 0

Key behavior
- Implementations should provide RAII semantics for opening/closing the source and a `readSource` that returns true when a value was read successfully and false on EOF or error.

Notes
- Implementations in this repo: `FileTelemetrySrc` (file-based) and `SocketTelemetrySrc` (socket-based).

Related files
- logging/inc/FileTelemetrySrc.hpp
- logging/inc/SocketTelemetrySrc.hpp (implementation in logging/src)
