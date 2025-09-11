include(CheckLibraryExists)
include(GNUInstallDirs)
option(RMATRIX_BUILD_TESTS "Build RMatrix's unit tests" ON)

add_library(rmatrix SHARED src/rmatrix.c)
target_include_directories(rmatrix
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

set_target_properties(rmatrix
    PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/rmatrix/Debug"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/rmatrix/Release"
        LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/rmatrix/Debug"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/rmatrix/Release"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/rmatrix/Debug"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/rmatrix/Release"
)

target_link_libraries(rmatrix PUBLIC rashunal::rashunal)

check_library_exists(m abs "" NEED_LIBM)
if (NEED_LIBM)
    target_link_libraries(rmatrix PUBLIC m)
endif()

target_compile_definitions(rmatrix PRIVATE RMATRIX_BUILD_DLL)
if (MSVC)
    target_compile_options(rmatrix PRIVATE /W4)
else()
    target_compile_options(rmatrix PRIVATE -Wall -Werror)
endif()

if (RMATRIX_BUILD_TESTS)
    FetchContent_Declare(
        Unity
        GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
        GIT_TAG master
    )
    FetchContent_MakeAvailable(Unity)
    FetchContent_GetProperties(Unity)

    add_subdirectory(test)
endif()

set_target_properties(
    rmatrix
    PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

install(
    TARGETS rmatrix
    EXPORT rmatrixTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT rmatrixTargets
    FILE rmatrixTargets.cmake
    NAMESPACE rmatrix::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/rmatrix"
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/rmatrixConfig.cmake
    DESTINATION lib/cmake/rmatrix
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/rmatrixConfig.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/rmatrix"
)
