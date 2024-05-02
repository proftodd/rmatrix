add_library(rmatrix SHARED src/rmatrix.c)

target_include_directories(rmatrix
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        ${RASHUNAL_INCLUDE_DIR}
)

target_link_libraries(rmatrix
    PRIVATE
        ${RASHUNAL_LIB}
        m
)

target_compile_options(rmatrix PRIVATE -Werror)

add_subdirectory(test)

set(PUBLIC_HEADERS_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/include/rmatrix.h"
)

set_target_properties (
    rmatrix
    PROPERTIES
    PUBLIC_HEADER "${PUBLIC_HEADERS_FILES}"
)

install(
    TARGETS rmatrix
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
