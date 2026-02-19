#include "LogManager.hpp"
#include "ConsoleSink.hpp"
#include "FileSink.hpp"
#include "FileTelemetrySrc.hpp"
#include "LogFormatter.hpp"
#include "Cpu_policy.hpp"
#include "ThreadPool.hpp"
#include "SomeIPTelemetrySrcImpl.hpp"


int main(){
    LogManager logger;
    logger.addSink(std::make_unique<ConsoleSink>());
    logger.addSink(std::make_unique<FileSink>("app.log"));

    FileTelemetrySrc telemetry("data.txt");
    if (!telemetry.openSource()){
        std::cerr << "Failed to open telemetry file!" << std::endl;
        return 1;
    }

    auto& gpuClient = SomeIPTelemetrySourceImpl::getInstance();

    std::size_t numWorkers = 3;
    ThreadPool pool(numWorkers);

    gpuClient.setEventCallback([&logger, &pool](float gpuLoad) {
        pool.submit([gpuLoad, &logger]() {
            if (gpuLoad >= 0.0f) {
                std::string gpuData = std::to_string(gpuLoad);
                auto maybeMsg = LogFormatter<Gpu_policy>::formatDataToLogMsg(gpuData);
                if (maybeMsg.has_value()){
                    logger.log(maybeMsg.value());
                    logger.flush();
                }
            }
        });
    });
    std::string line;
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    while (telemetry.readSource(line)) {

        // --- CPU processing ---
        pool.submit([line, &logger]() {
            auto maybeMsg = LogFormatter<Cpu_policy>::formatDataToLogMsg(line);
            if (maybeMsg)
                logger.log(maybeMsg.value());
        });

        
        pool.submit([line, &logger]() {
            auto maybeMsg = LogFormatter<Ram_policy>::formatDataToLogMsg(line);
            if (maybeMsg)
                logger.log(maybeMsg.value());
        });
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    logger.flush();
    std::cout << "All telemetry data logged concurrently." << std::endl;
    
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return 0;
}
