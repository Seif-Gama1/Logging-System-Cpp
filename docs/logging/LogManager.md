File: logging/inc/LogManager.hpp

Purpose
- Central log router and buffer manager. Buffers LogMessage objects in a RingBuffer and routes them to configured sinks.

Public API
- class LogManager
  - LogManager(std::size_t bufferCapacity = 100)
  - void log(const LogMessage& source)
  - void addSink(std::unique_ptr<ILogSink> sink)
  - void flush()

Key behavior and recent fixes
- Maintains separate mutexes for the buffer (`bufferMutex`) and sinks (`sinksMutex`).
- `log()` attempts to push into the ring buffer; if the buffer is full it synchronously routes the message to sinks rather than silently dropping it.
- `flush()` drains the buffer by popping messages under `bufferMutex` and routing each message.

Thread-safety
- Buffer and sink access are serialized separately to reduce contention. `LogManager` is safe to call concurrently from multiple threads.

Notes
- The ring buffer `tryPush` is non-blocking; design trade-offs include either synchronous fallback (current) or alternative strategies: blocking, drop-oldest, or resize.

Related files
- logging/inc/RingBuffer.hpp
- logging/inc/ILogSink.hpp
- logging/src/LogManager.cpp
