#pragma once
#include <string_view>
#include "enums.hpp"

class Cpu_policy{
    public:
        static constexpr TelemetrySrc_enum context = TelemetrySrc_enum::CPU;
        static constexpr std::string_view unit = "%";
        static constexpr float WARNING = 75.0f;
        static constexpr float CRITICAL = 90.0f;

        static constexpr SeverityLvl_enum inferSeverity(float val){
        // constexpr SeverityLvl_enum Cpu_policy::inferSeverity(float val){
            return (val > Cpu_policy::CRITICAL) ? SeverityLvl_enum::CRITICAL
                : (val > Cpu_policy::WARNING)  ? SeverityLvl_enum::WARNING
                :                    SeverityLvl_enum::INFO;
        }
};

