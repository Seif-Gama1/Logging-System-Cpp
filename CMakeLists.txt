cmake_minimum_required(VERSION 3.12)

project(CPP_Project_Logging_System LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(CommonAPI REQUIRED PATHS /usr/local/include/CommonAPI-3.2)
find_package(CommonAPI-SomeIP REQUIRED)
find_package(vsomeip3 REQUIRED)

include_directories(
    logging/src
    logging/inc
    src-gen
    ${COMMONAPI_INCLUDE_DIRS}
    ${COMMONAPI_SOMEIP_INCLUDE_DIRS}
    ${VSOMEIP3_INCLUDE_DIRS}
)

file(GLOB GENERATED_SOURCES "src-gen/v1/omnimetron/gpu/*.cpp")

add_library(gpu_generated STATIC ${GENERATED_SOURCES})

target_include_directories(gpu_generated PUBLIC 
    ${CMAKE_SOURCE_DIR}/src-gen
    /usr/local/include/CommonAPI-3.2
)

add_subdirectory(logging)
add_subdirectory(app)

add_executable(Telemetry_server
    logging/src/GPUTelemetryServer.cpp
    ${GENERATED_SOURCES}
)

target_link_libraries(Telemetry_server PRIVATE
    gpu_generated   
    logging
    CommonAPI
    CommonAPI-SomeIP
    vsomeip3
)
