cmake_minimum_required(VERSION 3.27)
project(svg_rendering)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
set(OUTPUT_EXECUTABLE_NAME "svg_rendering")

#set(CMAKE_VERBOSE_MAKEFILE ON) #For debug

file(GLOB_RECURSE CPP_FILES CONFIGURE_DEPENDS "src/*.cpp")


add_executable(${PROJECT_NAME} WIN32 ${CPP_FILES} "src/api/parser/StringParser.h" "src/api/parser/StringParser.cpp")
#add_executable(${PROJECT_NAME} src/main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
add_library(rapidxml INTERFACE)

target_link_libraries(${PROJECT_NAME} PRIVATE gdiplus)