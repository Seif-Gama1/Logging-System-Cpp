add_library(logging
    src/ConsoleSink.cpp
    src/FileSink.cpp
    src/LogManager.cpp
    src/LogMessage.cpp
    src/SafeFile.cpp
    src/SafeSocket.cpp
    src/FileTelemetrySrc.cpp
    src/SocketTelemetrySrc.cpp
    # src/LogFormatter.cpp
    # src/Policy_classes/Cpu_policy.cpp
    # src/Policy_classes/Gpu_policy.cpp
    # src/Policy_classes/Ram_policy.cpp
)

target_include_directories(logging PUBLIC 
                            ${CMAKE_CURRENT_SOURCE_DIR}/inc
                            ${CMAKE_CURRENT_SOURCE_DIR}/inc/Policy_classes
                            ${CMAKE_SOURCE_DIR}/third_party/magic_enum/include/magic_enum
                          )