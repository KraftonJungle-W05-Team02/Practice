#include "rbtree.h"

void rbtree_transplant(rbtree *t, node_t *u, node_t *v){
    if(u->parent == t->nil){
        t->root = v;
    }
    else if(u == u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }

    v->parent = u->parent;
}

int rbtree_erase(rbtree *t, node_t *z) {
    // TODO: implement erase

    node_t *y = z;
    color_t y_original_color = y->color;

    node_t *x;
    if(z->left == t->nil){
        x = z->right;
        rbtree_transplant(t, z, z->right);
    }
    else if(z->right == t->nil){
        x = z->left;
        rbtree_transplant(t, z, z->left);
    }
    else{
        y = z->right;

        while(y->left != t->nil){
           y = y->left;
        }
        y_original_color = y->color;
        x = y->right;

        if(y != z->right){
            rbtree_transplant(t, y, y->right);

            y->right = z->right;
            y->right->parent = y;
        }
        else{
            x->parent = y;
        }

        rbtree_transplant(t, z, y);
        
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if(y_original_color == RBTREE_BLACK){
        rbtree_erase_fixup(t,x);
    }

    free(z);

    return 0;
}