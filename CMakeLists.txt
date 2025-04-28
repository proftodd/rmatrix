cmake_minimum_required(VERSION 3.15...4.0 FATAL_ERROR)
project(rmatrix LANGUAGES C VERSION 0.0.1)

include(FetchContent)

FetchContent_Declare(
    rashunal
    GIT_REPOSITORY https://github.com/proftodd/rashunal.git
    GIT_TAG main
)

set(RASHUNAL_BUILD_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(rashunal)

enable_testing()

add_subdirectory(rmatrix)
add_subdirectory(external)
