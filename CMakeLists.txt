cmake_minimum_required(VERSION 3.27)
project(svg_rendering)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")
#set(OUTPUT_EXECUTABLE_NAME "svg_render")

# DOWNLOAD RAYLIB LIBRARY
if (WIN32 AND NOT CYGWIN)

endif ()

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


file(GLOB_RECURSE CPP_FILES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(${PROJECT_NAME} src/main.cpp
		src/Renderer.cpp
		src/Renderer.h
		src/element/Vector2D.h
		src/element/Element.h ${CPP_FILES}
		src/element/Gradient.h)

add_library(rapidxml INTERFACE)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})