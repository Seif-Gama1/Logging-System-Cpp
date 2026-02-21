File: logging/inc/LogMessage.hpp

Purpose
- Value type representing a single formatted log entry. Encapsulates metadata (name, timestamp, context, severity) and the payload text.

Public API
- LogMessage(std::string name, std::string timeStamp, std::string context, std::string severity, std::string payload)
- friend std::ostream& operator<<(std::ostream& os, const LogMessage& msg)

Key behavior
- The ostream operator outputs a bracketed, human-readable representation used by ConsoleSink and FileSink.

Notes
- The constructor moves string arguments for efficiency.
- LogMessage is used throughout the logging pipeline and is intentionally a lightweight immutable container once constructed.

Related files
- logging/src/LogMessage.cpp
- logging/inc/LogFormatter.hpp
