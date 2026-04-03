add_executable( binary_test_exe regular_tree_test.cpp)
add_executable( binary_search_test_exe binary_search_test.cpp)

target_link_libraries( binary_test_exe PRIVATE gtest gtest_main binary_tree_lib)
target_link_libraries( binary_search_test_exe PRIVATE gtest gtest_main binary_search_tree_lib )

target_compile_definitions( binary_test_exe PRIVATE DATA_DIR="${TEST_DATA_DIR}/binary")
target_compile_definitions( binary_search_test_exe PRIVATE DATA_DIR="${TEST_DATA_DIR}/binary" )

gtest_discover_tests( binary_test_exe )
gtest_discover_tests( binary_search_test_exe )