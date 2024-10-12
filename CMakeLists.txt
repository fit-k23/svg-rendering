cmake_minimum_required(VERSION 3.29)
project(svg_rendering)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(svg_rendering src/main.cpp)

add_library(rapidxml INTERFACE)

target_link_libraries(${PROJECT_NAME} PUBLIC -lgdiplus)