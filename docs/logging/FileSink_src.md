File: logging/src/FileSink.cpp

Purpose
- Implements `FileSink` methods to format LogMessage and write to disk using SafeFile.

Highlights
- `write()` formats a LogMessage and writes the bytes via `SafeFile::write`.
- Ensures thread-safety around file writes with an internal mutex.

Notes
- The `format` helper currently appends an extra newline; sinks and consumers should expect text output that may include newlines.
