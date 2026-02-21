File: logging/inc/Policy_classes/Cpu_policy.hpp

Purpose
- Policy class describing CPU telemetry semantics for LogFormatter.

Public details
- static constexpr TelemetrySrc_enum context = TelemetrySrc_enum::CPU
- static constexpr std::string_view unit = "%"
- static constexpr float WARNING = 75.0f
- static constexpr float CRITICAL = 90.0f
- static constexpr SeverityLvl_enum inferSeverity(float val)

Notes
- `inferSeverity` is constexpr and returns CRITICAL/WARNING/INFO depending on thresholds.
- Used as `LogFormatter<Cpu_policy>`.
