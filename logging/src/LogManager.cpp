#include "LogManager.hpp"

void LogManager::route(const LogMessage& msg) {
    // Only lock sinksMutex while iterating/writing to sinks so buffer operations
    // don't contend on the same lock.
    std::lock_guard<std::mutex> lock(sinksMutex);
    for (const auto& sink : sinks){
        sink->write(msg);
    }
}

void LogManager::addSink(std::unique_ptr<ILogSink> sink){
    std::lock_guard<std::mutex> lock(sinksMutex);
    sinks.emplace_back(std::move(sink));
}

void LogManager::log(const LogMessage& source) {
    // Try to push into the buffer under bufferMutex. If buffer is full,
    // immediately route the message synchronously to avoid silent drops.
    {
        std::lock_guard<std::mutex> lock(bufferMutex);
        if (buffer.tryPush(source)) {
            return;
        }
    }

    // Buffer was full; write directly to sinks to avoid losing this message.
    route(source);
}

void LogManager::flush() {
    // Pop messages from buffer and route them. Keep pop under bufferMutex,
    // and route under sinksMutex (route does that already).
    while (true) {
        std::optional<LogMessage> msgOpt;
        {
            std::lock_guard<std::mutex> lock(bufferMutex);
            msgOpt = buffer.tryPop();
        }

        if (!msgOpt) {
            break; // buffer empty
        }

        route(*msgOpt);
    }
}