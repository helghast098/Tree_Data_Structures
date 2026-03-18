#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include "binary_node.hpp"
#include <string>
class BinaryTree {
    public:
        // Constructors
        BinaryTree() = default;
        BinaryTree( const std::string &node_data_str );

        // Destructor
        ~BinaryTree();

        // methods
        bool is_full_binary(); // checks if the graph is full binary
        void clear();  // clears the graph

    private:
        BinaryNode *head = nullptr;

};

#endif