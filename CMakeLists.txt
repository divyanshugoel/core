cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# Define global variables for scripts and suboordinate CMakeLists
option(BUILD_DOC		"Build documentation"	OFF)
option(BUILD_SERVER		"Build for server"		OFF)
option(BUILD_EXAMPLES	"Build Examples"		ON)
option(BUILD_GRAPHICS	"Build Graphics"		ON)

set(CMAKE_BUILD_TYPE "Release")

# Global default company name

# Absolute paths to common directories
set(PROJECT_DIR_ROOT ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "Root directory" FORCE)
set(PROJECT_DIR_CMAKE ${PROJECT_DIR_ROOT}/cmake CACHE STRING "Root 'CMake' directory" FORCE)
set(PROJECT_DIR_CMAKE_INPUT ${PROJECT_DIR_CMAKE}/input CACHE STRING "CMake input directory" FORCE)
set(PROJECT_DIR_CMAKE_MODULES ${PROJECT_DIR_CMAKE}/modules CACHE STRING "CMake modules directory" FORCE)
set(PROJECT_DIR_EXTERNAL ${PROJECT_DIR_ROOT}/external CACHE STRING "External dependencies directory" FORCE)

set(PROJECT_DIR_SRC ${PROJECT_DIR_ROOT}/src CACHE STRING "Root 'Src' directory" FORCE)
set(PROJECT_DIR_BUILD ${PROJECT_DIR_ROOT}/build CACHE STRING "Root 'Build' directory" FORCE)
set(PROJECT_DIR_LIB ${CMAKE_BINARY_DIR}/lib CACHE STRING "Root 'lib' directory" FORCE)
set(PROJECT_DIR_BIN ${CMAKE_BINARY_DIR}/bin CACHE STRING "Root 'bin' directory" FORCE)
set(PROJECT_DIR_INCLUDE ${CMAKE_BINARY_DIR}/include CACHE STRING "Root 'Include' directory" FORCE)
set(PROJECT_DIR_LOGS ${CMAKE_BINARY_DIR}/logs CACHE STRING "Root 'logs' directory" FORCE)
set(PROJECT_DIR_INSTALL ${PROJECT_DIR_ROOT} CACHE STRING "Install directory" FORCE)

if (NOT DEFINED PROJECT_CACHE_ROOT)
	set(PROJECT_CACHE_ROOT ${PROJECT_DIR_ROOT}/.. CACHE STRING "Location of folder where cross-built cache data can be stored (defaults to parent directory)" FORCE)
endif()

# Include common custom modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_DIR_CMAKE_MODULES})
include(projectUtils)
include(projectExternals)

# Clear logs
project_clear_logs()

# Retrieve Git hash for use throughout scripts
project_get_git_short_hash(_git_hash)

# Initialize vcpkg (must be called prior to the first project() call)
project_vcpkg_init()

project(FleetCore)
project_init()

# Find all external dependencies (see comments in projectExternals.cmake)

message(STATUS "Processing external dependencies" )
project_process_dependencies()

message(STATUS "Processing  source code")
# Add default include directories
# Top-level (so we can use "assets/", etc.")
include_directories(${PROJECT_DIR_ROOT})
# SRC directory (typical include)
include_directories(${PROJECT_DIR_SRC}) 

# Process Src directory tree
message(STATUS "Processing CMakeLists files" )
add_subdirectory(src)

project_post_build()
