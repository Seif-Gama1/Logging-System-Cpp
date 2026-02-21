File: logging/inc/Policy_classes/Gpu_policy.hpp

Purpose
- Policy class describing GPU telemetry semantics for LogFormatter.

Public details
- static constexpr TelemetrySrc_enum context = TelemetrySrc_enum::GPU
- static constexpr std::string_view unit = "%"
- static constexpr float WARNING = 70.0f
- static constexpr float CRITICAL = 85.0f
- static constexpr SeverityLvl_enum inferSeverity(float val)

Notes
- `inferSeverity` returns CRITICAL/WARNING/INFO depending on thresholds.
- Used as `LogFormatter<Gpu_policy>`.
