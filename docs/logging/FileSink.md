File: logging/inc/FileSink.hpp

Purpose
- File-backed log sink. Appends formatted log messages to a file using a POSIX wrapper (SafeFile).

Public API / classes
- class FileSink : public ILogSink
  - FileSink(const std::string& path)
  - FileSink(FileSink&&)
  - FileSink& operator=(FileSink&&)
  - void write(const LogMessage& msg) override

Key behavior
- Writes formatted text to an on-disk file. Uses a mutex to serialize concurrent writes.
- Format performed by a private `format(const LogMessage&)` helper which produces a textual representation.

Notes
- Uses SafeFile which wraps low-level POSIX read/write/open semantics.
- Writes are performed under a lock to avoid interleaved writes from multiple threads.
- File is opened with flags O_WRONLY | O_APPEND | O_CREAT.

Usage example
- logger.addSink(std::make_unique<FileSink>("app.log"));

Related files
- logging/inc/ILogSink.hpp
- logging/src/FileSink.cpp
- logging/inc/SafeFile.hpp
