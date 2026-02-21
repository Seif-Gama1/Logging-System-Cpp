File: logging/src/SocketTelemetrySrc.cpp

Purpose
- Socket-based implementation of `ITelemetrySrc` that connects to an IPv4 TCP telemetry emitter and reads textual telemetry.

Highlights
- `openSource()` builds a sockaddr_in and calls `connect` on the underlying SafeSocket.
- `readSource()` reads bytes from the socket into a buffer and returns the data as a string (false on disconnect).

Notes
- The implementation expects simple single-line payloads and uses `SafeSocket` for FD management.
