#pragma once
#include "ILogSink.hpp"

class ConsoleSink final : public ILogSink{
    public:
        void write(const LogMessage & msg) override;
};