File: logging/src/SafeSocket.cpp

Purpose
- Implementation of SafeSocket. Provides RAII lifecycle and wrappers around POSIX socket functions.

Highlights
- Throws std::system_error on bind/connect/listen failures to surface OS errors cleanly.
- `send`/`receive` throw when socket closed.
- Move ctor/assignment transfer ownership of fd.

Notes
- `accept()` is commented out; careful if adding that path since constructor semantics would need to support fd takeover.
