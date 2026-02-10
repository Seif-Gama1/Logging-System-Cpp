#pragma once
#include <string_view>
#include "enums.hpp"

class Ram_policy {
public:
    static constexpr TelemetrySrc_enum context = TelemetrySrc_enum::RAM;
    static constexpr std::string_view unit = "MB";
    static constexpr float WARNING = 8192.0f;
    static constexpr float CRITICAL = 16384.0f;

    static constexpr SeverityLvl_enum inferSeverity(float val){
        return (val > CRITICAL) ? SeverityLvl_enum::CRITICAL
            : (val > WARNING)  ? SeverityLvl_enum::WARNING
            : SeverityLvl_enum::INFO;
    }
};