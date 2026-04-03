#ifndef RED_BLACK
#define RED_BLACK

#include "binary_tree.hpp"

class RBTree: public BinaryTree {

    public:
    virtual bool search( int val ) const override;
    void insert( int val );
    bool erase( int val );/
};


#endif
