#pragma once

#include "LogManager.hpp"
#include "ConsoleSink.hpp"
#include "FileSink.hpp"
#include "FileTelemetrySrc.hpp"
// #include "SocketTelemetrySrc.hpp"
#include "LogFormatter.hpp"
#include "Cpu_policy.hpp"
#include "ThreadPool.hpp"
#include "SomeIPTelemetrySrcImpl.hpp"

#include <chrono>
#include <thread>
#include <memory>

#define DEFAULT_PARSE_RATE_MS 0
#define DEFAULT_LOG_DELAY_MS 0

struct AppConfig {
    bool enableCpu = true;
    bool enableRam = true;
    bool enableGpu = true;
    bool enableConsoleSink = true;
    bool enableFileSink = true;

    int parseRateMs = DEFAULT_PARSE_RATE_MS;
    int logDelayMs = DEFAULT_LOG_DELAY_MS;

    std::size_t numWorkers = 3;
    std::size_t gpuWorkers = 1;
};

class DataLogger{
public:
    explicit DataLogger(AppConfig cfg, const std::string& telemetryFile = "data.txt");
    ~DataLogger();

    void start(); /* runs the main processing loop (reads telemetry, dispatches tasks) */

private:
    AppConfig config;
    LogManager logger;
    ThreadPool pool;
    ThreadPool gpuPool;
    FileTelemetrySrc telemetry;
    // SocketTelemetrySrc sock_telemtery;
    SomeIPTelemetrySourceImpl& gpuClient;
};