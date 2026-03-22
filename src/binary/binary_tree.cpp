#include "binary/binary_tree.hpp"
#include <queue>
#include <unordered_map>
#include <sstream>
#include <stdexcept>
#include <algorithm>

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

// constructor
void populate_node( std::stringstream& nodes_val_str, std::queue<BinaryNode *>& q, bool& is_head_processed, const BinaryNode *head) {
    if ( q.empty() ) {
        throw TreeException("BinaryTree::BinaryTree - No node found for entry");
    }

    BinaryNode *node = q.front();
    q.pop();

    std::string node_val;
    int node_to_set = 0; // setting up left child first

    while ( std::getline( nodes_val_str, node_val, ' ') ) {
        // setting head value
        if ( !is_head_processed ) {
            node->val = std::stoi( node_val );
            is_head_processed = true;
            continue;
        }

        // left child
        if ( node_to_set == 0 ) {
            node->left_child = new BinaryNode( std::stoi( node_val ), node );
            q.push( node->left_child );
        }
        // right child
        else if ( node_to_set == 1 ) {
            node->right_child = new BinaryNode( std::stoi( node_val ), node );
            q.push( node->right_child );
        }
        else {
            if ( node == head ) {
                throw TreeException("BinaryTree::BinaryTree - String initializer has bad form: More than 3 values in first parse");
            }
            throw TreeException("BinaryTree::BinaryTree - String initializer has bad form: More than 2 values between , , after first parse");
        }
        ++node_to_set;
    }
}

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

int helper_balanced( BinaryNode * node) {
    if ( node == nullptr ) {
        return 0;
    }

    int left_height = helper_balanced( node->left_child );
    int right_height = helper_balanced( node->right_child );

    if ( left_height == -1 || right_height == -1 || abs( left_height - right_height ) > 1 ) {
        return -1;
    }

    return std::max( 1 + left_height, 1 + right_height );
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
            node_queue.push( head );
        }

        // parsing string for node values
        size_t node_end = node_data_str.find( ',', node_start );
        std::stringstream node_data;

        if ( node_end == std::string::npos ) {
            node_data.str( node_data_str.substr( node_start, node_data_str.length() - node_start ) );
            node_start = node_data_str.length();
        }
        else if ( node_start == node_end ) {
            if ( node_queue.empty() ) {
                //throw TreeException( "BinaryTree::BinaryTree - no node found for empty entry " );
                break; // will break early. All other nodes will be ignores and converted to leaf nodes
            }
            node_queue.pop();
            node_start = node_end + 1;
            continue;
        }
        else {
            node_data.str( node_data_str.substr( node_start, node_end - node_start ) );
            node_start = node_end + 1;
        }

        // setup up node with children
        populate_node( node_data, node_queue, is_head_processed, head );
    }
    this->head = head;
}

// deconstructor
BinaryTree::~BinaryTree() {
    this->clear();
}

void CopyTree( BinaryNode *copy, BinaryNode *original ) {
    if ( original == nullptr || copy == nullptr) {
        return;
    }
    
    if ( original->left_child != nullptr  ) {
        copy->left_child = new BinaryNode( original->left_child->val );
        CopyTree( copy->left_child, original->left_child );
    }

    if ( original->right_child != nullptr  ) {
        copy->right_child = new BinaryNode( original->right_child->val );
        CopyTree( copy->right_child, original->right_child );
    }
}

// function overload
const BinaryTree& BinaryTree::operator=( const BinaryTree &rhs ) {
    this->clear();
    if ( this->head != nullptr ) {
        head = new BinaryNode(0);
    }
    CopyTree( this->head, rhs.head );
    return *this;
}

void BinaryTree::clear() {
    clear_help( this->head );
    this->head = nullptr;
}

bool BinaryTree::is_full_binary() {
    return full_binary_help( this->head );
}

bool BinaryTree::is_balanced() {
    return helper_balanced( this->head ) != -1;
}