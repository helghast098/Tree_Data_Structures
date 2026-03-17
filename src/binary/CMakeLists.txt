add_library(
    binary_algo_lib
    STATIC binary_tree_algos.cpp
)

target_include_directories(
    binary_algo_lib
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)