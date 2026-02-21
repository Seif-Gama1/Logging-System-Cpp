File: logging/inc/enums.hpp

Purpose
- Defines small enums used by the logging system for sink types, severity levels, and telemetry source kinds.

Enums
- enum class LogSinkType_enum : uint8_t { CONSOLE = 1, FILE = 2, SOCKET = 3 }
- enum class SeverityLvl_enum : uint8_t { CRITICAL = 0, WARNING = 1, INFO = 2 }
- enum class TelemetrySrc_enum : uint8_t { CPU = 0, GPU = 1, RAM = 2 }

Notes
- Used by LogFormatter and policies to produce textual context and severity strings.
- `magic_enum` is used elsewhere to convert enum values to strings.
