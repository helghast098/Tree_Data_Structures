#include "binary/binary_tree_algos.hpp"
#include "gtest/gtest.h"

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

const std::string data_dir = DATA_DIR;

void data_parser(std::string &s) {
    int test_case = 0;
    // getting test number
    size_t current_str_pos =  s.find(':');
    if ( current_str_pos == std::string::npos) {
        return;
    }
    test_case = std::stoi( s.substr( 0, current_str_pos ) );
    current_str_pos += 2; // skips over :, ' '

    // getting test_data
    std::cerr << "Test Case: " << test_case << std::endl;

    while ( current_str_pos < s.length() ) {
        size_t index = s.find( ',', current_str_pos );
        std::stringstream node_data;
        if ( index == std::string::npos ) {
            node_data.str( s.substr( current_str_pos, s.length() - current_str_pos ) );
            current_str_pos = s.length();
        }
        else {
            node_data.str( s.substr( current_str_pos, index - current_str_pos ) );
            current_str_pos = index + 1;
        }
        node_data.clear();

        std::string node_val;
        bool is_parent = true;
        while ( std::getline( node_data, node_val, ' ') ) {
            if ( is_parent ) {
                std::cerr << "This is Parent: " << std::stoi(  node_val ) << std::endl;
                is_parent = false;
            }
            else {
                std::cerr << "Child: " << std::stoi( node_val ) << std::endl;
            }
        }
    }
}



TEST(EXAMPLE, Test) {
    std::ifstream input(data_dir + "/test_data.txt");
    ASSERT_TRUE(input.good()) << strerror(errno);
    std::string line;
    while(std::getline(input, line)) {
        data_parser(line);
    }
    input.close();
}
