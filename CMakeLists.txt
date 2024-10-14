cmake_minimum_required(VERSION 3.27)
project(svg_rendering)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")
#set(OUTPUT_EXECUTABLE_NAME "svg_render")

file(GLOB_RECURSE CPP_FILES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(${PROJECT_NAME} ${CPP_FILES})

add_library(rapidxml INTERFACE)

#set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${OUTPUT_EXECUTABLE_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC -lgdiplus)
