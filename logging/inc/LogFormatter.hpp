// #pragma once
// #include <string>
// #include <string_view>
// #include <chrono>
// #include <iomanip>
// #include <sstream>
// #include <optional>
// #include "LogMessage.hpp"
// #include "enums.hpp"
// #include <magic_enum.hpp>

// // Template LogFormatter: Policy provides thresholds, unit, context, inferSeverity
// template <typename Policy>
// class LogFormatter {
//     public:
//         static std::optional<LogMessage> formatDataToLogMsg(const std::string& raw);
//         static std::string msgDescription(float val);
//         static std::string currentTimeStamp();
// };


#pragma once
#include <string>
#include <string_view>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <optional>
#include <magic_enum.hpp>
#include "LogMessage.hpp"
#include "enums.hpp"
#include "Gpu_policy.hpp"
#include "Cpu_policy.hpp"
#include "Ram_policy.hpp"

template <typename Policy>
class LogFormatter {
public:
    static std::optional<LogMessage> formatDataToLogMsg(const std::string& raw) {
        try {
            float value = std::stof(raw);
            SeverityLvl_enum severity = Policy::inferSeverity(value);
            std::string payload = msgDescription(value);
            std::string timestamp = currentTimeStamp();

            return LogMessage{
                "Some App",
                timestamp,
                std::string(magic_enum::enum_name(Policy::context)),
                std::string(magic_enum::enum_name(severity)),
                payload
            };
        } 
        catch (const std::exception&) {
            return std::nullopt;
        }
    }

    static std::string msgDescription(float val) {
        std::ostringstream oss;
        oss << "Current " 
            << magic_enum::enum_name(Policy::context) 
            << " usage: " << val << Policy::unit;
        return oss.str();
    }

    static std::string currentTimeStamp() {
        auto now = std::chrono::system_clock::now();
        auto t_c = std::chrono::system_clock::to_time_t(now);
        std::ostringstream oss;
        oss << std::put_time(std::localtime(&t_c), "%F %T");
        return oss.str();
    }
};