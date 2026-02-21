File: logging/inc/FileTelemetrySrc.hpp

Purpose
- File-based telemetry source that implements `ITelemetrySrc` using `SafeFile`.

Public API
- class FileTelemetrySrc : public ITelemetrySrc
  - FileTelemetrySrc(const std::string& filePath, int flags = O_RDONLY)
  - bool openSource() override
  - bool readSource(std::string& out) override
  - std::string sourcePath() const override

Key behavior
- `openSource()` returns whether the underlying SafeFile is open.
- `readSource()` calls `SafeFile::readLine` and returns true if a line was read; returns false on EOF or error.

Notes
- `readSource` currently treats EOF the same as an error (returns false); an optional follow/tail behavior can be added if you need to keep reading appended data.
- FileTelemetrySrc is move-only (no copy semantics).

Related files
- logging/inc/ITelemetrySrc.hpp
- logging/inc/SafeFile.hpp
- logging/src/FileTelemetrySrc.cpp
