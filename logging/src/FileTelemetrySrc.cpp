#include "FileTelemetrySrc.hpp"

/* flags has default value O_RDONLY */
FileTelemetrySrc::FileTelemetrySrc(const std::string& filePath, int flags) 
    : 
    file(filePath, flags),
    path(filePath)
{

}

FileTelemetrySrc::FileTelemetrySrc(FileTelemetrySrc&& other)
    : 
    file(std::move(other.file)),
    path(std::move(other.path))
{

}
FileTelemetrySrc& FileTelemetrySrc::operator=(FileTelemetrySrc&& other){
    if (this != &other){
        file = std::move(other.file);
        path = std::move(other.path);
    }
    return *this;
}


bool FileTelemetrySrc::openSource() {
    return file.is_open();
}

bool FileTelemetrySrc::readSource(std::string& out) {
    if (!file.is_open()) return false;

    // char buffer[50];
    ssize_t bytesRead = file.readLine(out); // read one line using SafeFile
    if (bytesRead <= 0) {
        return false; // EOF or error
    }

    // buffer[bytesRead] = '\0';
    // out = std::string(buffer);
    return true;
}

std::string FileTelemetrySrc::sourcePath() const{
    return path;
}