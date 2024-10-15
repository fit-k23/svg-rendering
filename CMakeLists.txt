cmake_minimum_required(VERSION 3.27)
project(svg_rendering)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")
#set(OUTPUT_EXECUTABLE_NAME "svg_render")

file(GLOB_RECURSE CPP_FILES CONFIGURE_DEPENDS "src/*.cpp")

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
	raylib
	GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
	GIT_TAG 5.0
	GIT_PROGRESS TRUE
)

if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
	FetchContent_MakeAvailable(raylib)
endif()

#add_executable(${PROJECT_NAME} ${CPP_FILES})
add_executable(${PROJECT_NAME} src/main.cpp)

add_library(rapidxml INTERFACE)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
#target_link_libraries(${PROJECT_NAME} PUBLIC -lgdiplus)

#target_link_directories(${PROJECT_NAME} PRIVATE raylib)
#add_library(raylib STATIC IMPORTED GLOBAL)
#set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
#set_target_properties(${PROJECT_NAME} PROPERTIES
#	IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
#	IMPORTED_LOCATION_DEBUG "${FETCHCONTENT_BASE_DIR}/raylib-src/lib/raylib.lib")
#
#MESSAGE("${FETCHCONTENT_BASE_DIR}/raylib-src/lib/raylib.dll")

#set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${OUTPUT_EXECUTABLE_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})