#pragma once
#include "LogMessage.hpp"
#include "ILogSink.hpp"
#include <memory>
#include <vector>
#include <string>
#include <mutex>
#include "RingBuffer.hpp"

class LogManager{
    private:
        std::vector <std::unique_ptr<ILogSink>>  sinks;
        RingBuffer<LogMessage> buffer;
        std::mutex writeMutex;

        void route(const LogMessage& msg);
    public:
        LogManager(
            std::size_t bufferCapacity = 100
        ): buffer(bufferCapacity)
        {

        }

        LogManager(const LogManager& other) = delete;
        LogManager(LogManager&& other) =  delete;
        LogManager& operator = (const LogManager& other) = delete;
        LogManager& operator = (LogManager&& other) = delete;

        void log(const LogMessage& source);
        void addSink(std::unique_ptr<ILogSink> sink);
        void flush();
};
