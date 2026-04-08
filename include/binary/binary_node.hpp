#ifndef BINARY_NODE_H
#define BINARY_NODE_H

enum class ColorType {
    RED,
    BLACK
};

class BinaryNode {
    public:
    // Constructor
    BinaryNode(int val): val(val){};
    BinaryNode(int val, BinaryNode *parent_val): val(val), parent(parent_val){};
    BinaryNode(int val, BinaryNode *parent_val, ColorType color ): val(val), parent(parent_val), color(color) {};
    //
    int val;
    ColorType color {ColorType::BLACK};
    BinaryNode *parent {nullptr};
    BinaryNode *left_child {nullptr};
    BinaryNode *right_child {nullptr};
};
#endif