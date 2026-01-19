#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>

class LogMessage {
    private:
        std::string name;
        std::string timestamp;
        std::string context;
        std::string severity;
        std::string payload;
    public:
        // LogMessage() = delete;
        LogMessage(std::string name,
                    std::string timeStamp,
                    std::string context,
                    std::string severity,
                    std::string payload
                );

        friend std::ostream& operator<<(std::ostream& os ,const LogMessage& msg);
};
