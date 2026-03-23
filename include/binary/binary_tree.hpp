#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include "binary_node.hpp"
#include <string>
#include <vector>

enum class DFS_TYPE {
    POSTORDER,
    INORDER,
    PREORDER
};

class BinaryTree {
    public:

        // Constructors
        BinaryTree() = default;
        BinaryTree( const std::string &node_data_str );

        // Destructor
        ~BinaryTree();

        // methods
        void clear();  // clears the graph
        bool is_full_binary(); // checks if the graph is full binary
        bool is_balanced(); // checks if the grap is balanced
        const BinaryTree& operator=( const BinaryTree& rhs );
        std::vector<int> dfs( DFS_TYPE type = DFS_TYPE::PREORDER );
    private:
        BinaryNode *head = nullptr;
};

#endif