#include "binary/binary_tree_algos.hpp"
#include "gtest/gtest.h"

#include <fstream>
#include <string>
#include <string_view>
#include <iostream>
#include <sstream>
#include <queue>

const std::string data_dir = DATA_DIR;


BinaryNode* binary_tree_initializer( const std::string &node_data_str ) {
    BinaryNode *head = nullptr;
    bool is_head_processed = false;

    // getting node_data
    size_t node_start = 0; 
    std::queue< BinaryNode* > node_queue;

    while ( node_start < node_data_str.length() ) {
        if ( !is_head_processed ) {
            head = new BinaryNode(0);
            is_head_processed = true;
            node_queue.push( head );
        }

        // getting nodes substring
        size_t node_end = node_data_str.find( ',', node_start );
        std::stringstream node_data;

        if ( node_end == std::string::npos ) {
            node_data.str( node_data_str.substr( node_start, node_data_str.length() - node_start ) );
            node_start = node_data_str.length();
        }
        else {
            node_data.str( node_data_str.substr( node_start, node_end - node_start ) );
            node_start = node_end + 1;
        }
        node_data.clear();

        // parsing values from nodes substring
        std::string node_val;
        int node_should_set = 0; // identifies which node value should be set: 0 (parent),  1 (left child), 2 (right child)
        BinaryNode *node = node_queue.front();
        node_queue.pop();
        while ( std::getline( node_data, node_val, ' ') ) {

            if ( node_should_set == 0 ) {
                node->val = std::stoi( node_val ); // redundant, but helpful when debugging
                std::cerr << "Parent " << node->val << std::endl;
            }
            else if ( node_should_set == 1 ) {
                node->left_child = new BinaryNode( std::stoi( node_val ), node );
                node_queue.push( node->left_child );
                std::cerr << "CH1 " << node->left_child->val << std::endl;
            }
            else {
                node->right_child = new BinaryNode( std::stoi( node_val ), node );
                node_queue.push( node->right_child );
                std::cerr << "CH2 " << node->right_child->val << std::endl;
            }
            ++node_should_set;
        }
        std::cerr << "\n";
    }
    return head;
}

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

    BinaryNode *head = binary_tree_initializer( s.substr( node_data_start ) ); // produces memory leak righ now
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
