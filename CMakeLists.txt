###############################################################################
cmake_minimum_required (VERSION 3.13)

project (libcmdline VERSION 0.0.1
                 DESCRIPTION "A c++ library for commandline applications"
                 LANGUAGES CXX)
###############################################################################


# set output directories to "bin"
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# compiler settings
###############################################################################
# C++11 is required
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# warning level
add_compile_options (-Wall -Wextra -Wpedantic -fstack-protector-all)

# check dependencies
###############################################################################
include (CheckSymbolExists)
check_symbol_exists (getopt "unistd.h" HAVE_GETOPT)
check_symbol_exists (getopt_long "getopt.h" HAVE_GETOPTLONG)

# preprocessor definitions
###############################################################################
if (HAVE_GETOPT)
    add_compile_definitions (HAVE_GETOPT)
endif ()
if (HAVE_GETOPTLONG)
    add_compile_definitions (HAVE_GETOPTLONG)
endif ()
if (WIN32)
    add_compile_definitions (HAVE_WINDOWS)
endif ()

# target cmdline (main library)
###############################################################################
add_library (cmdline)
set (LIB_DIR lib)
set (LIB_SOURCES
    ${LIB_DIR}/console.cpp
    ${LIB_DIR}/cmdline.cpp
)

target_sources (cmdline PRIVATE ${LIB_SOURCES})
target_include_directories (cmdline
    PUBLIC ${LIB_DIR})

# target cmdline-unittest (unit test code)
###############################################################################
if (WITH_UNITTESTS)

    add_executable (cmdline-unittest)

    target_compile_definitions (cmdline-unittest PRIVATE WITH_UNITTESTS)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options (cmdline-unittest PRIVATE -Wno-write-strings --coverage)
        target_link_libraries (cmdline-unittest PRIVATE gcov)
    endif()

    target_sources(cmdline-unittest PRIVATE unittest/unittest.cpp ${LIB_SOURCES})
    target_include_directories (cmdline-unittest PRIVATE ${LIB_DIR})
endif ()

# example demo application
###############################################################################
if (WITH_DEMO)
    add_executable (example)

    target_link_libraries (example PRIVATE cmdline)
    target_sources(example PRIVATE example/example.cpp)
    target_include_directories (example PRIVATE ${LIB_DIR})
endif ()
