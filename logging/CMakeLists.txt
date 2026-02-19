add_library(logging
    src/ConsoleSink.cpp
    src/FileSink.cpp
    src/LogManager.cpp
    src/LogMessage.cpp
    src/SafeFile.cpp
    src/SafeSocket.cpp
    src/FileTelemetrySrc.cpp
    src/SocketTelemetrySrc.cpp
    src/SomeIPTelemetrySrcImpl.cpp
    src/GPUTelemetryServer.cpp
    # src/LogFormatter.cpp
)

file(GLOB GENERATED_SOURCES "${CMAKE_SOURCE_DIR}/src-gen/v1/omnimetron/gpu/*.cpp")
target_sources(logging PRIVATE ${GENERATED_SOURCES})

target_include_directories(logging PUBLIC 
                            ${CMAKE_CURRENT_SOURCE_DIR}/inc
                            ${CMAKE_CURRENT_SOURCE_DIR}/inc/Policy_classes
                            ${CMAKE_SOURCE_DIR}/third_party/magic_enum/include/magic_enum
                            ${CMAKE_SOURCE_DIR}/src-gen
                            /usr/local/include/CommonAPI-3.2 
                        )


target_link_libraries(logging
    ${COMMONAPI_LIBRARIES}
    ${COMMONAPI_SOMEIP_LIBRARIES}
    ${VSOMEIP3_LIBRARIES}
)