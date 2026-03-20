#include "binary/binary_tree.hpp"
#include "gtest/gtest.h"

#include <fstream>
#include <string>
#include <string_view>
#include <iostream>
#include <sstream>
#include <queue>

const std::string data_dir = DATA_DIR;

bool data_parser( const std::string &s,  int &test_case, int &expected_result, std::string &nodes_str ) {
    // getting test number
    size_t test_num_end =  s.find( ':' );
    if ( test_num_end == std::string::npos ) {
        return false;
    }

    test_case = std::stoi( s.substr( 0, test_num_end ) );
    std::cerr << "Test Case: " << test_case << std::endl;

    // getting test expected result
    size_t  test_expected_start = test_num_end + 2;
    size_t  test_expected_end =  s.find( '|', test_expected_start );
    if ( test_expected_end == std::string::npos ) {
        return false;
    }

    expected_result = std::stoi( s.substr( test_expected_start, test_expected_end - test_expected_start ) );
    std::cerr << "Expected: " << expected_result << std::endl;


    // getting test_data
    size_t node_data_start = test_expected_end + 2;
    if ( node_data_start >= s.length() ) {
        return true;
    }

    nodes_str = s.substr( node_data_start );
    return true;
}


TEST(BinaryTree, IsFullBinary) {
    std::ifstream input(data_dir + "/full_binary.txt");
    ASSERT_TRUE( input.good() ) << strerror( errno );
    std::string line;

    int test_case = 0;
    int expected_result = 0;
    std::string nodes_str;
    while(std::getline(input, line)) {
        if ( !data_parser( line, test_case, expected_result, nodes_str ) ) {
            continue;
        }

        BinaryTree tree( nodes_str );

        bool got = tree.is_full_binary();
        std::cerr << "Got: " << got << std::endl;

        ASSERT_EQ( expected_result, got );
        nodes_str = "";

        std::cerr << "\n\n";
    }
    input.close();
}

TEST(BinaryTree, IsBalanced) {
    std::ifstream input(data_dir + "/balanced.txt");
    ASSERT_TRUE( input.good() ) << strerror( errno );
    std::string line;

    int test_case = 0;
    int expected_result = 0;
    std::string nodes_str;
    while(std::getline(input, line)) {
        if ( !data_parser( line, test_case, expected_result, nodes_str ) ) {
            continue;
        }

        BinaryTree tree( nodes_str );

        bool got = tree.is_balanced();
        std::cerr << "Got: " << got << std::endl;

        ASSERT_EQ( expected_result, got );
        nodes_str = "";

        std::cerr << "\n\n";
    }
    input.close();
}
