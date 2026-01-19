#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <vector>

class SafeFile{
    private:
        int fd{-1};
    public:
        SafeFile() = delete;
        SafeFile(const std::string& filename, int flags);
        ~SafeFile();

        SafeFile(const SafeFile& other) = delete;
        SafeFile& operator=(const SafeFile& other) = delete;

        SafeFile(SafeFile&& other);
        SafeFile& operator=(SafeFile&& other);

        // APIs
        ssize_t write(const void* buf, size_t size);
        ssize_t read(void* buf, size_t size);
        bool is_open();
        ssize_t readLine(std::string& out);
        // int getFd(){
        //     return fd;
        // }
};