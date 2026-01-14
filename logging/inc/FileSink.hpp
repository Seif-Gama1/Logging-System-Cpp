#pragma once
#include "ILogSink.hpp"
#include <utility>
#include <iostream>
#include <fstream>

class FileSink final : public ILogSink{
    private:
        std::ofstream file;
    public:
        FileSink() = delete;
        FileSink(const std::string& path);

        FileSink(const FileSink&) = delete;
        FileSink& operator=(const FileSink&) = delete;

        FileSink(FileSink&&) noexcept;
        FileSink& operator=(FileSink&&) noexcept;


        void write(const LogMessage & msg) override;
};