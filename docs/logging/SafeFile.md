File: logging/inc/SafeFile.hpp

Purpose
- Lightweight RAII wrapper around POSIX file descriptors. Provides move-only semantics and convenience read/write helpers including a readLine method.

Public API
- SafeFile(const std::string& filename, int flags)
- ~SafeFile()
- SafeFile(SafeFile&&)
- SafeFile& operator=(SafeFile&&)
- ssize_t write(const void* buf, size_t size)
- ssize_t read(void* buf, size_t size)
- bool is_open()
- ssize_t readLine(std::string& out)

Key behavior
- Uses `open`, `read`, `write`, and `close` syscalls.
- `readLine` reads byte-by-byte until '\n' or EOF and returns number of bytes read (0 on EOF without content, -1 on error).

Notes
- The class is intentionally non-copyable but movable.
- Callers should check `is_open()` before using read/write.

Related files
- logging/src/SafeFile.cpp
- logging/inc/FileTelemetrySrc.hpp
