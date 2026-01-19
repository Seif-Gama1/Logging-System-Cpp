#include "LogManager.hpp"
#include "ConsoleSink.hpp"
#include "FileSink.hpp"
#include "FileTelemetrySrc.hpp"


int main() {
    // // LogManager logger;

    // // logger.addSink(std::make_unique<ConsoleSink>());
    // // logger.addSink(std::make_unique<FileSink>("app.log"));

    // // logger.log(LogMessage("test app1","18912874", "Init", "Low", "Action1"));
    // // logger.log(LogMessage("test app2","18915874", "Core", "High", "Action2"));
    // // logger.log(LogMessage("test app2","18919874", "Core", "Very High", "Action3"));

    // // logger.flush();

    // FileTelemetrySrc telemetry("data.txt");

    // if (!telemetry.openSource()) {
    //     std::cerr << "Failed to open file!" << std::endl;
    //     return 1;
    // }

    // std::string line;
    // while (telemetry.readSource(line)) {
    //     std::cout << "Read from telemetry source: " << line << std::endl;
    // }

    // std::cout << "End of file reached." << std::endl;
    // return 0;

    // return 0;

    // --- Setup Logger ---
    LogManager logger;
    logger.addSink(std::make_unique<ConsoleSink>());
    logger.addSink(std::make_unique<FileSink>("app.log"));

    // --- Setup Telemetry Source ---
    FileTelemetrySrc telemetry("data.txt");  // your dummy telemetry file
    if (!telemetry.openSource()) {
        std::cerr << "Failed to open telemetry file!" << std::endl;
        return 1;
    }

    // --- Read telemetry and log ---
    std::string line;
    int counter = 1;
    while (telemetry.readSource(line)) {
        // Create a LogMessage from telemetry data
        LogMessage msg(
            "TelemetryApp",                    // app name
            std::to_string(counter),           // timestamp (dummy)
            "Sensor",                          // context
            "Info",                            // severity
            line                               // payload = the read value
        );

        logger.log(msg);  // send to all sinks
        counter++;
    }

    // Flush logs (writes FileSink to disk, ConsoleSink prints)
    logger.flush();

    std::cout << "All telemetry data logged." << std::endl;
    return 0;
}