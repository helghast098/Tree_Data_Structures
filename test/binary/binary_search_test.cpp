#include "binary/binary_search_tree.hpp"
#include "gtest/gtest.h"

#include <fstream>
#include <string>
#include <string_view>
#include <iostream>
#include <sstream>
#include <queue>

const std::string data_dir = DATA_DIR + std::string("/search_tree");

bool data_parser( const std::string &s,  int &test_case, std::string &expected_result, std::string &nodes_str ) {
    // getting test number
    size_t test_num_end =  s.find( ':' );
    if ( test_num_end == std::string::npos ) {
        return false;
    }

    test_case = std::stoi( s.substr( 0, test_num_end ) );
    std::cerr << "============== Test Case: " << test_case <<  " ============== " << std::endl;

    // getting test expected result
    size_t  test_expected_start = test_num_end + 2;
    size_t  test_expected_end =  s.find( '|', test_expected_start );
    if ( test_expected_end == std::string::npos ) {
        return false;
    }

    expected_result = s.substr( test_expected_start, test_expected_end - test_expected_start );
    std::cerr << "Expected: " << expected_result << std::endl;

    // getting test_data
    size_t node_data_start = test_expected_end + 2;
    if ( node_data_start >= s.length() ) {
        return true;
    }

    nodes_str = s.substr( node_data_start );
    return true;
}

std::vector<int> string_to_vec( const std::string& s ) {
    std::vector<int> vec;
    std::istringstream s_stream(s);
    std::string val;

    while ( std::getline( s_stream, val, ' ' ) ) {
        vec.push_back( std::stoi( val ) );
    }

    return vec;
}

// Insert
TEST( BinarySearchTree, Insert ) {

    std::ifstream input(data_dir + "/insert.txt");
    ASSERT_TRUE( input.good() ) << strerror( errno );
    std::string line;

    int test_case = 0;
    std::string expected_result;
    std::string nodes_str;
    while( std::getline( input, line ) ) {
        if ( !data_parser( line, test_case, expected_result, nodes_str ) ) {
            continue;
        }

        BinaryTree expected( nodes_str );
        BinarySearchTree result;
        std::vector<int> insert_array = string_to_vec( expected_result ); // 2 is used to skip to first number in expected list

        for ( int v: insert_array ) {
            result.insert( v );
        }

        bool res = result == expected;
        ASSERT_TRUE( res );

        nodes_str = "";

        std::cerr << "\n\n";
    }
    input.close();
}

// Search
TEST( BinarySearchTree, Erase ) {

    std::ifstream input(data_dir + "/erase.txt");
    ASSERT_TRUE( input.good() ) << strerror( errno );
    std::string line;

    int test_case = 0;
    std::string operation_arr;
    std::string nodes_str;
    while( std::getline( input, line ) ) {
        if ( !data_parser( line, test_case, operation_arr, nodes_str ) ) {
            continue;
        }

        BinaryTree expected( nodes_str );
        BinarySearchTree result;

        std::string insert_str = operation_arr.substr( 0, operation_arr.find( '/' ) );
        std::string erase_str = operation_arr.substr( operation_arr.find( '/' ) + 2 );


        std::vector<int> insert_arr = string_to_vec( insert_str ); // 2 is used to skip to first number in expected list
        std::vector<int> erase_arr = string_to_vec( erase_str );

        for ( int v: insert_arr ) {
            result.insert( v );
        }

        for ( int v: erase_arr ) {
            result.erase( v );
        }

        bool res = result == expected;
        ASSERT_TRUE( res );

        nodes_str = "";

        std::cerr << "\n\n";
    }
    input.close();
}