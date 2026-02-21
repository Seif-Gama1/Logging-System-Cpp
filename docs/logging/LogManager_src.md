File: logging/src/LogManager.cpp

Purpose
- Implementation of LogManager routing and buffering logic.

Highlights
- `log()` attempts to push into the in-memory ring buffer and falls back to synchronous `route()` if the buffer is full.
- `route()` locks sinks and iterates all configured sinks to call `sink->write(msg)`.
- `flush()` drains the buffer and routes items.

Threading notes
- Uses `bufferMutex` for buffer operations and `sinksMutex` for sink writes to minimize contention.

Operational note
- This design avoids silent drops by writing synchronously when buffer capacity is exhausted. If high-frequency telemetry causes sink contention, consider a bounded worker thread to drain the buffer instead of synchronous write.
