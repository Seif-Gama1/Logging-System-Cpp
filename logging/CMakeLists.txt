add_library(logging
    src/ConsoleSink.cpp
    src/FileSink.cpp
    src/LogManager.cpp
    src/LogMessage.cpp
)

target_include_directories(logging PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)