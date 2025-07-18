cmake_minimum_required(VERSION 3.15...4.0 FATAL_ERROR)
project(rmatrix LANGUAGES C VERSION 0.0.1)

include(FetchContent)

find_package(rashunal QUIET)

option(USE_LOCAL_RASHUNAL "Use local Rashunal project instead of fetching" ON)

if (NOT rashunal_FOUND)
if (USE_LOCAL_RASHUNAL)
    FetchContent_Declare(
        rashunal
        SOURCE_DIR /Users/john/workspace/rashunal
    )
else()
    FetchContent_Declare(
        rashunal
        GIT_REPOSITORY https://github.com/proftodd/rashunal.git
        GIT_TAG main
    )
    endif()

    set(RASHUNAL_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(rashunal)
endif()

enable_testing()

add_subdirectory(rmatrix)
