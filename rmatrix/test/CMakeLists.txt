add_library(Unity STATIC "${unity_SOURCE_DIR}/src/unity.c")
target_include_directories(Unity PUBLIC "${unity_SOURCE_DIR}/src")

set(CMAKE_BUILD_RPATH_USE_ORIGIN true)

add_executable(test_rmatrix_app src/test_rmatrix.c)
set_target_properties(test_rmatrix_app PROPERTIES
    BUILD_RPATH "@loader_path/..")
target_link_libraries(test_rmatrix_app PRIVATE rmatrix Unity)
target_include_directories(test_rmatrix_app PRIVATE ${PROJECT_SOURCE_DIR}/rmatrix/include)
add_test(test_rmatrix_suite test_rmatrix_app)
add_test(NAME valgrind_memcheck
         COMMAND valgrind --leak-check=full --error-exitcode=1 $<TARGET_FILE:test_rmatrix_app>)
