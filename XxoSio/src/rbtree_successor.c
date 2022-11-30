#include "rbtree.h"

// node_t *rbtree_successor(const rbtree *t, node_t *x){
//     if(x->right != t->nil){
//         return rbtree_min(x->right);
//     }

//     node_t *y = x->parent;

//     while(y != t->nil && x == y->right){
//         x = y;
//         y = y->parent;
//     }

//     return y;
// }