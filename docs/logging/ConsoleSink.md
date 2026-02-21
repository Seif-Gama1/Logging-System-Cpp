File: logging/inc/ConsoleSink.hpp

Purpose
- Log sink that prints LogMessage instances to standard output.

Public API
- class ConsoleSink final : public ILogSink
  - void write(const LogMessage & msg) override

Key behavior
- Uses an internal mutex to serialize console writes and avoid interleaving lines from concurrent threads.

Notes
- Very small and thread-safe; useful during development and tests.

Related files
- logging/src/ConsoleSink.cpp
- logging/inc/ILogSink.hpp
