#include "ConsoleSink.hpp"

void ConsoleSink::write(const LogMessage& msg){
    std::lock_guard<std::mutex> lock(writeMutex);
    std::cout << msg << std::endl;
}