File: logging/src/FileTelemetrySrc.cpp

Purpose
- Implements `FileTelemetrySrc` that reads telemetry lines from a file using `SafeFile`.

Highlights
- `readSource` uses `SafeFile::readLine` and returns true if bytes were read, false on EOF or error.

Notes
- If you need `tail -f` behaviour (keep reading appended lines), modify this implementation to sleep-and-retry on EOF instead of returning false.
