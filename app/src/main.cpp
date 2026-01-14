#include "LogManager.hpp"
#include "ConsoleSink.hpp"
#include "FileSink.hpp"


int main() {
    LogManager logger;

    logger.addSink(std::make_unique<ConsoleSink>());
    logger.addSink(std::make_unique<FileSink>("app.log"));

    logger.log(LogMessage("test app1","18912874", "Init", "Low", "Action1"));
    logger.log(LogMessage("test app2","18915874", "Core", "High", "Action2"));
    logger.log(LogMessage("test app2","18919874", "Core", "Very High", "Action3"));

    logger.flush();
    return 0;
}