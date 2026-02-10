#include "LogManager.hpp"

void LogManager::route(const LogMessage& msg) { 
    std::lock_guard<std::mutex> lock(writeMutex);
    for (const auto& sink : sinks){ 
        sink->write(msg);
    }
}

void LogManager::addSink(std::unique_ptr<ILogSink> sink){
    std::lock_guard<std::mutex> lock(writeMutex);
    sinks.emplace_back(std::move(sink));
}

void LogManager::log(const LogMessage& source) {
    std::lock_guard<std::mutex> lock(writeMutex);
    buffer.tryPush(source);
}

void LogManager::flush() {
    while (!buffer.isEmpty()) {
        auto msgOpt = buffer.tryPop();
        if (msgOpt) {
            const auto& msg = *msgOpt;
            route(msg);
        }
    }
}