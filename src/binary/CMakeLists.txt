add_library(
    binary_tree_lib
    STATIC binary_tree.cpp
)

add_library(
    binary_search_tree_lib
    STATIC binary_search_tree.cpp
)

target_include_directories(
    binary_tree_lib
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries( binary_search_tree_lib binary_tree_lib )