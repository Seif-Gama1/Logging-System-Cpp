File: logging/src/SafeFile.cpp

Purpose
- Implements SafeFile methods: open, read, write, readLine, move semantics and destructor.

Highlights
- `readLine` reads bytes one at a time until newline or EOF and returns byte count (0 on EOF without content).
- Errors return -1; callers must handle EOF vs error appropriately.

Notes
- Because `readLine` performs one-byte reads, this is a simple but not high-throughput approach — acceptable for small telemetry inputs.
