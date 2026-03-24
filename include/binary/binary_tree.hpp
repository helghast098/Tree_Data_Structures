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
        BinaryTree( const BinaryTree& other );
        BinaryTree( const std::string &node_data_str );

        // Destructor
        ~BinaryTree();

        // methods
        void clear();  // clears the graph
        bool is_full_binary() const; // checks if the graph is full binary
        bool is_balanced() const; // checks if the grap is balanced
        std::vector<int> dfs( DFS_TYPE type = DFS_TYPE::PREORDER ) const; // returns dfs search vector
        std::vector<int> bfs() const;
        int height() const;

        // operator overload
        const BinaryTree& operator=( const BinaryTree& rhs );
        bool operator==( const BinaryTree& other ) const;
    private:
        BinaryNode *head = nullptr;
};

#endif