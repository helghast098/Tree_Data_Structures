#ifndef RED_BLACK_HPP
#define RED_BLACK_HPP

#include "binary_tree.hpp"

class RBTree: public BinaryTree {

    public:
    virtual bool search( int val ) const override;
    void insert( int val );
    bool erase( int val );/
};


#endif
