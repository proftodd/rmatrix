add_library(Unity STATIC "${unity_SOURCE_DIR}/src/unity.c")
target_include_directories(Unity PUBLIC "${unity_SOURCE_DIR}/src")

add_executable(test_rmatrix_app src/test_rmatrix.c)
target_link_libraries(test_rmatrix_app rmatrix Unity)
add_test(test_rmatrix_suite test_rmatrix_app)
