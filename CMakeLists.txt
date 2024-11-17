cmake_minimum_required(VERSION 3.27)
project(svg_rendering)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
set(OUTPUT_EXECUTABLE_NAME "svg_rendering")

#set(CMAKE_VERBOSE_MAKEFILE ON) #For debug

file(GLOB_RECURSE CPP_FILES CONFIGURE_DEPENDS "src/*.cpp")


add_executable(${PROJECT_NAME} ${CPP_FILES} "src/element/utils/Gradient.cpp" "src/element/utils/Stop.h" "src/element/utils/Stop.cpp" "src/element/utils/LinearGradient.h" "src/element/utils/LinearGradient.cpp" "src/element/utils/RadialGradient.h" "src/element/utils/RadialGradient.cpp")
#add_executable(${PROJECT_NAME} src/main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR} OUTPUT_NAME ${OUTPUT_EXECUTABLE_NAME})
add_library(rapidxml INTERFACE)

target_link_libraries(${PROJECT_NAME} PRIVATE gdiplus)