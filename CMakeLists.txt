cmake_minimum_required(VERSION 3.16)

project(
    Trees
    DESCRIPTION "Tree Data Structures"
    LANGAUGES CXX
)

include(FetchContent)

FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)

include(CTest)
include(GoogleTest)

add_subdirectory(src)
add_subdirectory(test)