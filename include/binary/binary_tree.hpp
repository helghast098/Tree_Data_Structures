#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include "binary_node.hpp"
#include <string>
class BinaryTree {
    public:
        // Constructors
        BinaryTree() = default;
        BinaryTree( std::string const &node_data_str );

        // Destructor
        ~BinaryTree();

        // methods
        bool full_binary(); // checks if the graph is full binary
        void clear();  // clears the graph

    private:
        BinaryNode *head = nullptr;

};

#endif