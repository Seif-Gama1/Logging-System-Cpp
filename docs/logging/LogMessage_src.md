File: logging/src/LogMessage.cpp

Purpose
- Implements `LogMessage` constructor and the `operator<<` for textual output used by sinks.

Highlights
- Streams the log message fields in a bracketed format: `[name] [timestamp] [context] [severity] payload`.

Notes
- Keeps output formatting centralized for consistent sink outputs.
