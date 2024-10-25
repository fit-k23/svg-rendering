cmake_minimum_required(VERSION 3.27)
project(svg_rendering)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

#set(OUTPUT_EXECUTABLE_NAME "svg_render")

# DOWNLOAD RAYLIB LIBRARY
set(RAYLIB_NAME "raylib")
set(RAYLIB_TAG 5.0)
set(RAYLIB_ASSET "")

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	if (CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(RAYLIB_ASSET "raylib-5.0_linux_amd64.tar.gz")
	else ()
		set(RAYLIB_ASSET "raylib-5.0_linux_i386.tar.gz")
	endif ()
endif ()

if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	set(RAYLIB_ASSET "raylib-5.0_macos.tar.gz")
endif ()

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	if (CMAKE_SIZEOF_VOID_P EQUAL 8)
		if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
			message(STATUS "Project is compiled with MSVC")
			set(RAYLIB_ASSET "raylib-5.0_win64_msvc16.zip")
		elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
			message(STATUS "Project is compiled with MinGW/Clang")
			set(RAYLIB_ASSET "raylib-5.0_win64_mingw-w64.zip")
		endif()
	else ()
		if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
			message(STATUS "Project is compiled with MSVC")
			set(RAYLIB_ASSET "raylib-5.0_win32_msvc16.zip")
		elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
			message(STATUS "Project is compiled with MinGW/Clang")
			set(RAYLIB_ASSET "raylib-5.0_win32_mingw-w64.zip")
		endif()
	endif ()
endif ()
set(RAYLIB_RELEASE_URL https://github.com/raysan5/raylib/releases/download/${RAYLIB_TAG}/${RAYLIB_ASSET})

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
	${RAYLIB_NAME}
	URL ${RAYLIB_RELEASE_URL}
)

if (NOT ${RAYLIB_NAME}_POPULATED) # Have we downloaded raylib yet?
	FetchContent_MakeAvailable(${RAYLIB_NAME})
	set(RAYLIB_LIBRARY "${${RAYLIB_NAME}_SOURCE_DIR}/lib/")
	set(RAYLIB_INCLUDE "${PROJECT_SOURCE_DIR}/lib/${RAYLIB_NAME}")

	file(GLOB_RECURSE RAYLIB_HEADER_FILES "${${RAYLIB_NAME}_SOURCE_DIR}/include/*")
	message(STATUS "Copy include files to lib folder")
	foreach(FILE ${RAYLIB_HEADER_FILES})
#		message(STATUS "Copy ${${RAYLIB_NAME}_SOURCE_DIR} ${REL_PATH} to ${RAYLIB_INCLUDE}/${REL_PATH}")
		file(RELATIVE_PATH REL_PATH "${${RAYLIB_NAME}_SOURCE_DIR}/include" "${FILE}")
		configure_file("${FILE}" "${RAYLIB_INCLUDE}/${REL_PATH}" COPYONLY)
	endforeach()
endif()

#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#	message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

file(GLOB_RECURSE CPP_FILES CONFIGURE_DEPENDS "src/*.cpp")
#add_executable(${PROJECT_NAME} src/main.cpp ${CPP_FILES})

add_executable(${PROJECT_NAME} src/main.cpp)

#add_library(rapidxml INTERFACE)

target_include_directories(${PROJECT_NAME} PRIVATE ${RAYLIB_INCLUDE_DIR})

# Link Raylib library
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		find_library(RAYLIB raylib REQUIRED ${RAYLIB_LIBRARY})
		target_link_libraries(${PROJECT_NAME} PRIVATE ${RAYLIB})
	else ()
		find_library(RAYLIB raylib HINTS ${RAYLIB_LIBRARY})
		target_link_libraries(${PROJECT_NAME} PRIVATE ${RAYLIB})
	endif ()

	target_link_libraries(${PROJECT_NAME} PRIVATE gdi32 winmm)
else()
	find_library(RAYLIB raylib HINTS ${RAYLIB_LIBRARY})
	target_link_libraries(${PROJECT_NAME} PRIVATE ${RAYLIB})
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})