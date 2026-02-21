File: logging/inc/ILogSink.hpp

Purpose
- Abstract sink interface for log outputs (console, file, socket).

Public API
- class ILogSink
  - virtual void write(const LogMessage & msg) = 0
  - virtual ~ILogSink() = default

Key behavior
- Sinks implement `write` which is called by `LogManager::route` to persist or display a log message.

Implementations
- ConsoleSink (writes to stdout)
- FileSink (appends to file)

Related files
- logging/inc/ConsoleSink.hpp
- logging/inc/FileSink.hpp
- logging/src/*Sink.cpp
