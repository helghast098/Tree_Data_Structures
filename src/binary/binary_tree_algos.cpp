#include "binary/binary_tree_algos.hpp"

bool full_binary(BinaryNode *current_node) {
    if ( current_node == nullptr ) {
        return true;
    }

    if ( current_node->left_child == nullptr && current_node->right_child == nullptr ) {
        return true;
    }

    if ( current_node->left_child == nullptr || current_node->right_child == nullptr ) {
        return false;
    }

    return full_binary( current_node->left_child ) && full_binary( current_node->right_child );
}