#ifndef BINARY_NODE_H
#define BINARY_NODE_H

class BinaryNode {
    public:
    // Constructor
    BinaryNode(int val): val(val){};
    BinaryNode(int val, BinaryNode *parent_val): val(val), parent(parent_val){};

    //
    int val;
    BinaryNode *parent {nullptr};
    BinaryNode *left_child {nullptr};
    BinaryNode *right_child {nullptr};
};
#endif