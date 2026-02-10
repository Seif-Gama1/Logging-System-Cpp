#pragma once
#include "ILogSink.hpp"
#include "SafeFile.hpp"
#include <iostream>
#include <utility>
#include <fstream>
#include <fcntl.h>   // O_WRONLY, O_APPEND, O_CREAT, O_RDONLY, etc.
#include <unistd.h>  // open, close, write, read
#include <mutex>

class FileSink final : public ILogSink{
    private:
        SafeFile file;
        std::mutex writeMutex;
        std::string format(const LogMessage& msg);
        
        public:
        FileSink() = delete;
        FileSink(const std::string& path);
        
        FileSink(const FileSink& other) = delete;
        FileSink& operator=(const FileSink& other) = delete;
        
        FileSink(FileSink&& other);
        FileSink& operator=(FileSink&& other);
        
        void write(const LogMessage & msg) override;
};