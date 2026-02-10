#pragma once
#include <string_view>
#include "enums.hpp"

class Gpu_policy {
public:
    static constexpr TelemetrySrc_enum context = TelemetrySrc_enum::GPU;
    static constexpr std::string_view unit = "%";
    static constexpr float WARNING = 70.0f;
    static constexpr float CRITICAL = 85.0f;

    static constexpr SeverityLvl_enum inferSeverity(float val){
        return (val > CRITICAL) ? SeverityLvl_enum::CRITICAL
            : (val > WARNING)  ? SeverityLvl_enum::WARNING
            : SeverityLvl_enum::INFO;
    }
};

