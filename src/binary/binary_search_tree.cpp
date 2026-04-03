#include "binary/binary_search_tree.hpp"

// helper func.
BinaryNode* search_help( BinaryNode* node, int val ) {
    if ( node == nullptr ) {
        return nullptr;
    }

    if( node->val == val ) {
        return node;
    }
    else if ( node->val > val ) {
        return search_help( node->left_child, val );
    }
    else {
        return search_help( node->right_child, val );
    }
}

void insert_help( BinaryNode *node, int val ) {
    if ( node == nullptr ) {
        return;
    }

    // val greater than or = to node
    if ( node->val < val) {
        if ( node->right_child == nullptr ) {
            node->right_child = new BinaryNode( val, node );
            return;
        }
        else {
            insert_help( node->right_child, val );
        }
    }
    // val less than node
    else {
        if ( node->left_child == nullptr ) {
            node->left_child = new BinaryNode( val, node );
            return;
        }
        else {
            insert_help( node->left_child, val );
        }
    }
}

BinaryNode* find_least( BinaryNode* node ) {
    if ( node == nullptr ) {
        return nullptr;
    }

    if ( node->left_child != nullptr ) {
        return find_least( node->left_child );
    }

    return node;
}

// class func.
void BinarySearchTree::insert( int val ) {
    if ( this->head == nullptr ) {
        this->head = new BinaryNode( val );
    }
    else {
        insert_help( this->head, val );
    }
}

bool BinarySearchTree::erase( int val ) {
    BinaryNode* node = search_help( this->head, val );
    if ( node == nullptr ) {
        return false;
    }

    BinaryNode* parent = node->parent;
    BinaryNode* child = nullptr;

    // 1 child
    if ( ( node->left_child == nullptr ) ^ ( node->right_child == nullptr ) ) {
        child = node->left_child != nullptr ? node->left_child : node->right_child;
        child->parent = parent;
    }
    // 2 children
    else if ( ( node->left_child != nullptr ) && ( node->right_child != nullptr ) ) {
        // will need to store left child
        BinaryNode* right = node->right_child;
        BinaryNode* left = node->left_child;
        BinaryNode* new_parent = find_least( right );
        child = new_parent;
        
        // new_parent has 0 children
        if ( new_parent->right_child == nullptr ) {
            new_parent->parent->left_child = nullptr;
        }
        // new_parent has 1 child
        else {
            new_parent->right_child->parent = new_parent->parent;
            new_parent->parent->left_child = new_parent->right_child;
        }

        new_parent->parent = parent;

        new_parent->left_child = left;
        left->parent = new_parent;

        if ( new_parent != right ) {
            new_parent->right_child = right;
            right->parent = new_parent;
        }
    }

    // if root node removed
    if ( parent == nullptr ) {
        this->head = child;
    }
    else if ( parent->left_child == node ) {
        parent->left_child = child;
    }
    else {
        parent->right_child = child;
    }

    delete node;
    return true;
}

bool BinarySearchTree::search( int val ) const {
    return ( search_help( this->head, val ) != nullptr );
}
