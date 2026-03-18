#include "binary/binary_tree.hpp"
#include <queue>
#include <sstream>
// Constructor
BinaryTree::BinaryTree(  std::string const &node_data_str ) {
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
            }
            else if ( node_should_set == 1 ) {
                node->left_child = new BinaryNode( std::stoi( node_val ), node );
                node_queue.push( node->left_child );
            }
            else {
                node->right_child = new BinaryNode( std::stoi( node_val ), node );
                node_queue.push( node->right_child );
            }
            ++node_should_set;
        }
    }
    this->head = head;
}
