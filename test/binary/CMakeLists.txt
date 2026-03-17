add_executable( binary_test_exe test.cpp)

target_link_libraries( binary_test_exe PRIVATE gtest gtest_main binary_algo_lib)

target_compile_definitions( binary_test_exe PRIVATE DATA_DIR="${TEST_DATA_DIR}/binary")
gtest_discover_tests( binary_test_exe )