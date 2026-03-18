add_library(
    binary_tree_lib
    STATIC binary_tree.cpp
)

target_include_directories(
    binary_tree_lib
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)