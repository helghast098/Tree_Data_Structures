#include "binary/binary_tree.hpp"
#include "gtest/gtest.h"

#include <fstream>
#include <string>
#include <string_view>
#include <iostream>
#include <sstream>
#include <queue>

const std::string data_dir = DATA_DIR;

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

    while (std::getline( s_stream, val, ' ' ) ) {
        vec.push_back( std::stoi( val ) );
    }

    return vec;
}

TEST( BinaryTree, IsFullBinary ) {
    std::ifstream input( data_dir + "/full_binary.txt" );
    ASSERT_TRUE( input.good() ) << strerror( errno );
    std::string line;

    int test_case = 0;
    std::string expected_result;
    std::string nodes_str;
    while( std::getline( input, line ) ) {
        if ( !data_parser( line, test_case, expected_result, nodes_str ) ) {
            continue;
        }

        BinaryTree tree( nodes_str );

        bool got = tree.is_full_binary();
        std::cerr << "Got: " << got << std::endl;
        ASSERT_EQ( std::stoi( expected_result ), got );

        nodes_str = "";

        std::cerr << "\n\n";
    }
    input.close();
}

TEST( BinaryTree, IsBalanced ) {
    std::ifstream input( data_dir + "/balanced.txt" );
    ASSERT_TRUE( input.good() ) << strerror( errno );
    std::string line;

    int test_case = 0;
    std::string expected_result;
    std::string nodes_str;
    while( std::getline( input, line ) ) {
        if ( !data_parser( line, test_case, expected_result, nodes_str ) ) {
            continue;
        }

        BinaryTree tree( nodes_str );

        bool got = tree.is_balanced();
        std::cerr << "Got: " << got << std::endl;

        ASSERT_EQ( std::stoi( expected_result ), got );
        nodes_str = "";

        std::cerr << "\n\n";
    }
    input.close();
}

TEST( BinaryTree, EqualityOperator ) {
    std::ifstream input( data_dir + "/equals.txt" );
    ASSERT_TRUE( input.good() ) << strerror( errno );
    std::string line;

    int test_case = 0;
    std::string expected_result;
    std::string nodes_str;
    while( std::getline( input, line ) ) {
        if ( !data_parser( line, test_case, expected_result, nodes_str ) ) {
            continue;
        }

        bool expected_bool = expected_result[0] == '1';

        size_t start_indx = expected_result.length() == 2 ? 1 : 2;
        size_t length = expected_result.length() == 2 ? 0 : expected_result.length() - 3; // 3 removes the ending space and the expected val and space that follows it

        BinaryTree tree1( expected_result.substr( start_indx , length ) );
        BinaryTree tree2( nodes_str );

        bool got = ( tree1 == tree2 );
        std::cerr << "Got: " << got << std::endl;

        ASSERT_EQ( expected_bool, got );
        nodes_str = "";

        std::cerr << "\n\n";
    }
    input.close();
}

TEST( BinaryTree, DFS ) {
    std::ifstream input(data_dir + "/dfs.txt");
    ASSERT_TRUE( input.good() ) << strerror( errno );
    std::string line;

    int test_case = 0;
    std::string expected_result;
    std::string nodes_str;
    while( std::getline( input, line ) ) {
        if ( !data_parser( line, test_case, expected_result, nodes_str ) ) {
            continue;
        }

        DFS_TYPE type = ( expected_result[0] == '0' ) ? DFS_TYPE::PREORDER : ( expected_result[0] == '1' ) ? DFS_TYPE::INORDER : DFS_TYPE::POSTORDER;
        BinaryTree tree( nodes_str );

        std::vector<int> expected_dfs = string_to_vec( expected_result.substr( 2 ) ); // 2 is used to skip to first number in expected list
        std::vector<int> got_dsf = tree.dfs( type );

        ASSERT_EQ( expected_dfs, got_dsf );

        nodes_str = "";

        std::cerr << "\n\n";
    }
    input.close();

    
}

TEST( BinaryTree,  AssignmentOperator ) {
    std::ifstream input( data_dir + "/balanced.txt" );
    ASSERT_TRUE( input.good() ) << strerror( errno );
    std::string line;

    int test_case = 0;
    std::string expected_result;
    std::string nodes_str;
    while( std::getline( input, line ) ) {
        if ( !data_parser( line, test_case, expected_result, nodes_str ) ) {
            continue;
        }

        BinaryTree tree( nodes_str );

        BinaryTree copy = tree;

        ASSERT_TRUE( tree == copy );
        nodes_str = "";

        std::cerr << "\n\n";
    }
    input.close();
}
