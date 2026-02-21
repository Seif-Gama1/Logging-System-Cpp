File: logging/inc/LogFormatter.hpp

Purpose
- Template utility that converts raw telemetry strings into `LogMessage` objects using a policy type (Cpu_policy, Gpu_policy, Ram_policy).

Public API
- template<typename Policy> class LogFormatter
  - static std::optional<LogMessage> formatDataToLogMsg(const std::string& raw)
  - static std::string msgDescription(float val)
  - static std::string currentTimeStamp()

Key behavior
- Parses a numeric value from a string, infers severity using Policy::inferSeverity, and builds a LogMessage with timestamp and a human-readable payload.
- Relies on magic_enum to convert enum values to strings for context and severity.

Notes
- Policy classes define: context, unit, WARNING, CRITICAL and inferSeverity(float).
- Formatters are header-only templates; there is a commented-out explicit-instantiation file `LogFormatter.cpp` (not needed for header-only use).

Usage
- auto maybeMsg = LogFormatter<Gpu_policy>::formatDataToLogMsg("42.5");
- if (maybeMsg) logger.log(*maybeMsg);

Related files
- logging/inc/Policy_classes/*
- logging/inc/LogMessage.hpp
