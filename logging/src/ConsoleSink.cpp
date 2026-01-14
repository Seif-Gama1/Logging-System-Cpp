#include "ConsoleSink.hpp"

void ConsoleSink::write(const LogMessage& msg){
    std::cout << msg << std::endl;
}