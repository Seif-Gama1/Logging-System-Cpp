#pragma once
#include "ILogSink.hpp"
#include <mutex>

class ConsoleSink final : public ILogSink{
    private:
        std::mutex writeMutex;
    public:

        ConsoleSink() = default;
        ~ConsoleSink() override = default;

        ConsoleSink(const ConsoleSink &) = default;
        ConsoleSink &operator=(const ConsoleSink &) = default;
        ConsoleSink(ConsoleSink &&) = default;
        ConsoleSink &operator=(ConsoleSink &&) = default;
        void write(const LogMessage & msg) override;
};