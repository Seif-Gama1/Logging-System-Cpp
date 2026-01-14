#pragma once
#include "LogMessage.hpp"
#include "ILogSink.hpp"
#include <memory>
#include <vector>
#include <string>

class LogManager{
    private:
        std::vector <std::unique_ptr<ILogSink>>  sinks;
        std::vector <LogMessage> buffer;

        void route(const LogMessage& msg);
    public:
        LogManager() = default;

        LogManager(const LogManager& other) = delete;
        LogManager(LogManager&& other) =  delete;
        LogManager& operator = (const LogManager& other) = delete;
        LogManager& operator = (LogManager&& other) = delete;

        void addSink(std::unique_ptr<ILogSink> sink);
        void log(const LogMessage& source);
        void flush();
};
