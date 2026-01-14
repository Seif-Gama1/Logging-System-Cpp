cmake_minimum_required(VERSION 3.12)

project(CPP_Project_Logging_System LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(logging)
add_subdirectory(app)