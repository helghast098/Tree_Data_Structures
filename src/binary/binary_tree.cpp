#include "binary/binary_tree.hpp"
#include <queue>
#include <sstream>
#include <stdexcept>

class TreeException: public std::exception {
    private:
    std::string message;

    public:
    TreeException(std::string msg): message(msg) {};

    const char* what() const noexcept override {
        return this->message.c_str();
    }
};

// helper functions
void clear_help( BinaryNode *node ) {
    if ( node == nullptr ) {
        return;
    }

    clear_help( node->left_child );
    clear_help( node->right_child );

    node->left_child = nullptr;
    node->right_child = nullptr;
    delete node;
}

bool full_binary_help( const BinaryNode *node ) {
    if ( node == nullptr ) {
        return true;
    }

    if ( node->left_child == nullptr && node->right_child == nullptr ) {
        return true;
    }

    if ( node->left_child == nullptr || node->right_child == nullptr  ) {
        return false;
    }

    return full_binary_help( node->left_child ) && full_binary_help( node->right_child );



}

// constructor
BinaryTree::BinaryTree( const std::string &node_data_str ) {
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

        if ( node_queue.empty() ) {
            throw TreeException("string initializer for Tree has bad form. Please see test cases for example format");
        }
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

// deconstructor
BinaryTree::~BinaryTree() {
    this->clear();
}

// methods

void BinaryTree::clear() {
    clear_help( this->head );
    this->head = nullptr;
}

bool BinaryTree::is_full_binary() {
    return full_binary_help( this->head );
}