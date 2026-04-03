#include "binary_tree.hpp"

class BinarySearchTree: public BinaryTree {
    public:
        virtual bool search( int val ) const override;
        void insert( int val );
        bool erase( int val );
    private:
};