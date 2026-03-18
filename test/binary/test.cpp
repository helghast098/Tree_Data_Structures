#include "binary/binary_tree_algos.hpp"
#include "gtest/gtest.h"

#include <fstream>
#include <string>
#include <string_view>
#include <iostream>
#include <sstream>
#include <queue>

const std::string data_dir = DATA_DIR;

void data_parser( std::string &s ) {
    int test_case = 0;
    // getting test number
    size_t test_num_end =  s.find( ':' );
    if ( test_num_end == std::string::npos ) {
        return;
    }

    test_case = std::stoi( s.substr( 0, test_num_end ) );
    std::cerr << "Test Case: " << test_case << std::endl;

    // getting test expected result
    size_t  test_expected_start = test_num_end + 2;
    size_t  test_expected_end =  s.find( '|', test_expected_start );

    if ( test_expected_end == std::string::npos ) {
        return;
    }

    int expected_result = std::stoi( s.substr( test_expected_start, test_expected_end - test_expected_start ) );
    std::cerr << "Expected: " << expected_result << std::endl;


    // getting test_data
    size_t node_data_start = test_expected_end + 2;
    if ( node_data_start >= s.length() ) {
        return;
    }
}


TEST(EXAMPLE, Test) {
    std::ifstream input(data_dir + "/test_data.txt");
    ASSERT_TRUE(input.good()) << strerror(errno);
    std::string line;
    while(std::getline(input, line)) {
        data_parser(line);
        std::cerr << "\n\n";
    }
    input.close();
}
