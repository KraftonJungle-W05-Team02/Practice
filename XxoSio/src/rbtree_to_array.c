#include "rbtree.h"

int inorder_array(const rbtree *t, node_t *p, key_t *arr, int i);

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array

    node_t *tmp = t->root;    
    
    inorder_array(t, tmp, arr, 0);
    
    return 0;
}

int inorder_array(const rbtree *t, node_t *p, key_t *arr, int i){
    if(p == t->nil){
        return i;
    }

    i = inorder_array(t, p->left, arr, i);
    arr[i++] = p->key;
    i = inorder_array(t, p->right, arr, i);

    return i;
}