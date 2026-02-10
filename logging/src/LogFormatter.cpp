// #include "LogFormatter.hpp"
// #include "Cpu_policy.hpp"
// #include "Gpu_policy.hpp"
// #include "Ram_policy.hpp"

// // Define the template for these policies only
// template class LogFormatter<Cpu_policy>;
// template class LogFormatter<Gpu_policy>;
// template class LogFormatter<Ram_policy>;

// static std::optional<LogMessage> LogFormatter<Policy>::formatDataToLogMsg(const std::string& raw) {
//     try {
//         float value = std::stof(raw);
//         SeverityLvl_enum severity = Policy::inferSeverity(value);
//         std::string payload = msgDescription(value);
//         std::string timestamp = currentTimeStamp();

//         return LogMessage{
//             "Some App",
//             timestamp,
//             std::string(magic_enum::enum_name(Policy::context)),
//             std::string(magic_enum::enum_name(severity)),
//             payload
//         };
//     } 
//     catch (const std::exception&) {
//         return std::nullopt;  // in case of invalid string to float conversion
//     }
// }

// static std::string LogFormatter<Policy>::msgDescription(float val) {
//     std::ostringstream oss;
//     oss << "Current " 
//         << magic_enum::enum_name(Policy::context) 
//         << " usage: " << val << Policy::unit;
//     return oss.str();
// }

// static std::string LogFormatter<Policy>::currentTimeStamp() {
//     auto now = std::chrono::system_clock::now();
//     auto t_c = std::chrono::system_clock::to_time_t(now);
//     std::ostringstream oss;
//     oss << std::put_time(std::localtime(&t_c), "%F %T");
//     return oss.str();
// }