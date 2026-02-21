add_executable(app src/main.cpp)
# add_executable(app src/someip/main.cpp)

# target_link_libraries(app PRIVATE logging
#     # CommonAPI
#     # CommonAPI-SomeIP
#     # vsomeip3
# )

target_include_directories(app PRIVATE 
    ${CMAKE_SOURCE_DIR}/logging/inc
    ${CMAKE_SOURCE_DIR}/src-gen
    /usr/local/include/CommonAPI-3.2
)

# Ensure generated CommonAPI SOME/IP sources are compiled into the app so
# their registration static initializers are present at runtime.
file(GLOB GENERATED_SOURCES "${CMAKE_SOURCE_DIR}/src-gen/v1/omnimetron/gpu/*.cpp")
target_sources(app PRIVATE ${GENERATED_SOURCES})
# Add facade implementation
target_sources(app PRIVATE src/DataLogger.cpp)
target_link_libraries(app PRIVATE 
    logging
    gpu_generated
    CommonAPI
    CommonAPI-SomeIP
    vsomeip3
)