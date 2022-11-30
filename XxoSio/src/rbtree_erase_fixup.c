#include "rbtree.h"

void rbtree_erase_fixup(rbtree *t, node_t *x) {
    while(x != t->root && x->color != RBTREE_BLACK){
        node_t *w;

        if(x == x->parent->right){
            w = x->parent->right;

            // case1 
            if(w->color = RBTREE_RED){
                w->color = RBTREE_BLACK;
                x->parent->color = RBTREE_RED;
                left_rotate(t, x->parent);
            }
            // case2
            if(w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK){
                w->color = RBTREE_RED;
                x = x->parent;
            }
            // case3
            else{
                if(w->right->color == RBTREE_BLACK){
                    w->left->color = RBTREE_BLACK;
                    w->color = RBTREE_RED;

                    right_rotate(t, w);

                    w = x->parent->right;
                }

                // case4
                w->color = x->parent->color;
                x->parent->color = RBTREE_BLACK;
                w->right->color = RBTREE_BLACK;

                left_rotate(t, x->parent);

                x = t->root;
            }
        }
        else{
            w = x->parent->left;

            if(w->color == RBTREE_RED){
                w->color = RBTREE_BLACK;
                x->parent->color = RBTREE_RED;

                right_rotate(t, x->parent);

                w = x->parent->left;
            }
            else{
                if(w->left->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK){
                    w->right->color = RBTREE_BLACK;
                    w->color = RBTREE_RED;

                    left_rotate(t, w);

                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = RBTREE_BLACK;
                w->left->color = RBTREE_BLACK;

                right_rotate(t, x->parent);
                x = t->root;
            }
        }
    }

    x->color = RBTREE_BLACK;
}