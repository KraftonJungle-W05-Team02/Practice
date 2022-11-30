#include "rbtree.h"

void free_node(rbtree *t, node_t *x) {
    // 후위 순회 방식으로 RB Tree 내의 노드 메모리 반환
    if (x->left != t->nil){
        free_node(t, x->left);
    }

    if (x->right != t->nil){
        free_node(t, x->right);
    }

    free(x);
    x = NULL;
}

void delete_rbtree(rbtree *t) {
    // TODO: reclaim the tree nodes's memory

    if (t->root != t->nil){
        free_node(t, t->root);
    }

    free(t->nil);
    free(t);
}