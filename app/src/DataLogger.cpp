#include "DataLogger.hpp"

#include <iostream>

DataLogger::DataLogger(AppConfig cfg, const std::string& telemetryFile)
: config(std::move(cfg)), logger(150), pool(config.numWorkers), gpuPool(config.gpuWorkers), telemetry(telemetryFile), gpuClient(SomeIPTelemetrySourceImpl::getInstance()) {
    if (config.enableConsoleSink)
        logger.addSink(std::make_unique<ConsoleSink>());
    if (config.enableFileSink)
        logger.addSink(std::make_unique<FileSink>("app.log"));

    if (config.enableGpu) {
        gpuClient.setEventCallback([this](float gpuLoad) {

            gpuPool.submit([this, gpuLoad]() {
                if (gpuLoad >= 0.0f) {
                    std::string gpuData = std::to_string(gpuLoad);
                    auto maybeMsg = LogFormatter<Gpu_policy>::formatDataToLogMsg(gpuData);
                    if (maybeMsg.has_value()){
                        if (config.logDelayMs > 0)
                            std::this_thread::sleep_for(std::chrono::milliseconds(config.logDelayMs));
                        logger.log(maybeMsg.value());
                    }
                }
            });
        });
    }
}

DataLogger::~DataLogger() = default;

void DataLogger::start(){
    if (!telemetry.openSource()){
        std::cerr << "Failed to open telemetry file!" << std::endl;
        return;
    }

    std::string line;
    while (telemetry.readSource(line)) {
        if (config.enableCpu) {
            pool.submit([line, this]() {
                auto maybeMsg = LogFormatter<Cpu_policy>::formatDataToLogMsg(line);
                if (maybeMsg) {
                    if (config.logDelayMs > 0)
                        std::this_thread::sleep_for(std::chrono::milliseconds(config.logDelayMs));
                    logger.log(maybeMsg.value());
                }
            });
        }

        if (config.enableRam) {
            pool.submit([line, this]() {
                auto maybeMsg = LogFormatter<Ram_policy>::formatDataToLogMsg(line);
                if (maybeMsg) {
                    if (config.logDelayMs > 0)
                        std::this_thread::sleep_for(std::chrono::milliseconds(config.logDelayMs));
                    logger.log(maybeMsg.value());
                }
            });
        }

        if (config.parseRateMs > 0)
            std::this_thread::sleep_for(std::chrono::milliseconds(config.parseRateMs));
    }
    std::cout<<"Telemetry source done\n";

    logger.flush();
    std::this_thread::sleep_for(std::chrono::seconds(5));
}
