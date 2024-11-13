cmake_minimum_required(VERSION 3.27)
project(svg_rendering)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
set(OUTPUT_EXECUTABLE_NAME "svg_rendering")

#set(CMAKE_VERBOSE_MAKEFILE ON) #For debug

file(GLOB_RECURSE CPP_FILES CONFIGURE_DEPENDS "src/*.cpp")


add_executable(${PROJECT_NAME} ${CPP_FILES} "src/api/parser/StringParser.h" "src/api/parser/StringParser.cpp" "src/element/shape/PathPoint.h" "src/element/shape/PathPoint.cpp" "src/element/shape/NormPathPoint.h" "src/element/shape/NormPathPoint.cpp" "src/element/shape/QuadPathPoint.h" "src/element/shape/QuadPathPoint.cpp" "src/element/shape/CubicPathPoint.h" "src/element/shape/CubicPathPoint.cpp" "src/element/shape/ArcPathPoint.h" "src/element/shape/ArcPathPoint.cpp")
#add_executable(${PROJECT_NAME} src/main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
add_library(rapidxml INTERFACE)

target_link_libraries(${PROJECT_NAME} PRIVATE gdiplus)