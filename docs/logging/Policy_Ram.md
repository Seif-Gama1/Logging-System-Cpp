File: logging/inc/Policy_classes/Ram_policy.hpp

Purpose
- Policy class for RAM telemetry semantics used by LogFormatter.

Public details
- static constexpr TelemetrySrc_enum context = TelemetrySrc_enum::RAM
- static constexpr std::string_view unit = "MB"
- static constexpr float WARNING = 8192.0f
- static constexpr float CRITICAL = 16384.0f
- static constexpr SeverityLvl_enum inferSeverity(float val)

Notes
- Thresholds are sized for large-memory systems (values in MB).
- Used as `LogFormatter<Ram_policy>`.
