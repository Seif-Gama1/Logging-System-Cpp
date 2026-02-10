#pragma once 
#include <cstdint>


enum class LogSinkType_enum : uint8_t{
    CONSOLE = 1, 
    FILE = 2,
    SOCKET = 3
};

enum class SeverityLvl_enum : uint8_t{
    CRITICAL = 0,
    WARNING = 1, 
    INFO = 2 
};

enum class TelemetrySrc_enum : uint8_t{
    CPU = 0, 
    GPU = 1, 
    RAM = 2
};