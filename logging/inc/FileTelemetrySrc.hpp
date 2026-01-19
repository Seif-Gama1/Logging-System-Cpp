#pragma once
#include "ITelemetrySrc.hpp"
#include "SafeFile.hpp"
#include <string>

class FileTelemetrySrc : public ITelemetrySrc {
private:
    SafeFile file;
    std::string path;

public:
    FileTelemetrySrc(const std::string& filePath, int flags = O_RDONLY);

    FileTelemetrySrc(const FileTelemetrySrc& other) = delete;
    FileTelemetrySrc& operator=(const FileTelemetrySrc& other)  = delete;

    FileTelemetrySrc(FileTelemetrySrc&& other);
    FileTelemetrySrc& operator=(FileTelemetrySrc&& other);

    bool openSource() override;
    bool readSource(std::string& out) override;
    std::string sourcePath() const override;
};
