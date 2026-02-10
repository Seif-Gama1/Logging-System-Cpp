#include "LogManager.hpp"
#include "ConsoleSink.hpp"
#include "FileSink.hpp"
#include "FileTelemetrySrc.hpp"
#include "LogFormatter.hpp"
#include "Cpu_policy.hpp"
#include "ThreadPool.hpp"

/* sample code/Notes */
// SeverityLvl sev = SeverityLvl::WARNING;

/* uint8_t sev_val = static_cast<uint8_t>(sev); // OK, explicit cast
// Cannot do: int x = sev;   // error, strongly typed */

/* formatter:
    std::optional<LogMessage> formatDataToLogMsg(const std::string& raw);
    Sometimes, telemetry reading is valid → return LogMessage in the optional.
    Sometimes, telemetry reading is invalid / missing → return std::nullopt.
*/

/* constexpr SeverityLvl checkSeverity(float val) {
        if constexpr (Policy::context == TelemetrySrc::CPU)
            return (val > Policy::CRITICAL) ? SeverityLvl::CRITICAL : SeverityLvl::INFO;
        else
            return SeverityLvl::INFO;
    }
*/

// int main() {
//     // --- Setup Logger ---
//     LogManager logger;
//     logger.addSink(std::make_unique<ConsoleSink>());
//     logger.addSink(std::make_unique<FileSink>("app.log"));

//     // --- Setup Telemetry Source ---
//     FileTelemetrySrc telemetry("data.txt");  // your dummy telemetry file
//     if (!telemetry.openSource()) {
//         std::cerr << "Failed to open telemetry file!" << std::endl;
//         return 1;
//     }

//     // --- Read telemetry and log ---
//     std::string line;
//     int counter = 1;
//     while (telemetry.readSource(line)){
//         // Use LogFormatter with CPU policy to generate LogMessage
//         auto cpu_maybeMsg = LogFormatter<Cpu_policy>::formatDataToLogMsg(line);
//         auto gpu_maybeMsg = LogFormatter<Gpu_policy>::formatDataToLogMsg(line);
//         auto ram_maybeMsg = LogFormatter<Ram_policy>::formatDataToLogMsg(line);

//         if (cpu_maybeMsg.has_value()) {
//             logger.log(cpu_maybeMsg.value());
//         } else {
//             std::cout << "Failed to parse CPU telemetry line: " << line << std::endl;
//         }
//         if (gpu_maybeMsg.has_value()) {
//             logger.log(gpu_maybeMsg.value());
//         } else {
//             std::cout << "Failed to parse GPU telemetry line: " << line << std::endl;
//         }
//         if (ram_maybeMsg.has_value()) {
//             logger.log(ram_maybeMsg.value());
//         } else {
//             std::cout << "Failed to parse RAM telemetry line: " << line << std::endl;
//         }
//         counter++;
//     }

//     logger.flush();

//     std::cout << "All telemetry data logged." << std::endl;
//     return 0;
// }

int main() {
    // --- Setup Logger ---
    LogManager logger;
    logger.addSink(std::make_unique<ConsoleSink>());
    logger.addSink(std::make_unique<FileSink>("app.log"));

    // --- Setup Telemetry Source ---
    FileTelemetrySrc telemetry("data.txt");  
    if (!telemetry.openSource()) {
        std::cerr << "Failed to open telemetry file!" << std::endl;
        return 1;
    }

    // --- Setup Thread Pool ---
    std::size_t numWorkers = 3; // one for CPU, GPU, RAM or more
    ThreadPool pool(numWorkers);

    std::string line;
    int counter = 0;

    while (telemetry.readSource(line)) {
        counter++;

        // --- Submit CPU processing ---
        pool.submit([line, &logger]() {
            auto maybeMsg = LogFormatter<Cpu_policy>::formatDataToLogMsg(line);
            if (maybeMsg) logger.log(maybeMsg.value());
            else std::cerr << "Failed to parse CPU telemetry: " << line << "\n";
        });

        // --- Submit GPU processing ---
        pool.submit([line, &logger]() {
            auto maybeMsg = LogFormatter<Gpu_policy>::formatDataToLogMsg(line);
            if (maybeMsg) logger.log(maybeMsg.value());
            else std::cerr << "Failed to parse GPU telemetry: " << line << "\n";
        });

        // --- Submit RAM processing ---
        pool.submit([line, &logger]() {
            auto maybeMsg = LogFormatter<Ram_policy>::formatDataToLogMsg(line);
            if (maybeMsg) logger.log(maybeMsg.value());
            else std::cerr << "Failed to parse RAM telemetry: " << line << "\n";
        });
    }

    // The pool destructor will wait for all tasks to finish
    // Ensure any pending logs are flushed
    logger.flush();

    std::cout << "All telemetry data logged concurrently." << std::endl;
    return 0;
}
