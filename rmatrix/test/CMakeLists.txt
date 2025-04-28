add_executable(test_rmatrix_app src/test_rmatrix.c)
target_link_libraries(test_rmatrix_app rmatrix Unity)
target_include_directories(test_rmatrix_app PRIVATE
    $<TARGET_PROPERTY:rmatrix,INTERFACE_INCLUDE_DIRECTORIES>)
add_test(test_rmatrix_suite test_rmatrix_app)
