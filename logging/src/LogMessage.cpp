#include "LogMessage.hpp"

LogMessage::LogMessage(std::string name,
                       std::string timeStamp,
                       std::string context,
                       std::string severity,
                       std::string payload
                    )
                    : name(std::move(name)), 
                    timestamp(std::move(timeStamp)), 
                    context(std::move(context)), 
                    severity(std::move(severity)),
                    payload(std::move(payload)) 
{
    
}
                
                
std::ostream& operator << ( std::ostream& os ,const LogMessage& msg){
    os << "[" << msg.name << "] "
       << "[" << msg.timestamp << "] "
       << "[" << msg.context << "] "
       << "[" << msg.severity << "] "
       << msg.payload << "\n";

    return os;
}