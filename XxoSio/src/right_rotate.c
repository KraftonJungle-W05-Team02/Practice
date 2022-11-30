#include "rbtree.h"

node_t *right_rotate(rbtree *t, node_t *x) {
    // TODO: implement insert

    // x의 왼쪽 자식노드인 y를 설정
    node_t *y = x->left;
    // x의 왼쪽 자식 노드를 y의 오른쪽 자식 노드로 변경
    x->left = y->right;

    // y의 오른쪽 자식 노드가 nil 노드가 아닐 경우
    if(y->right != t->nil){
        // y의 오른쪽 자식 노드의 부모 노드를 x로 변경
        y->right->parent = x;
    }

    // y의 부모 노드를 x의 부모 노드로 변경
    y->parent = x->parent;

    // x의 부모 노드가 nil 노드일 경우
    if(x->parent == t->nil){
        // 트리의 루트 노드를 y로 변경
        t->root = y;
    }
    // x가 x의 부모 노드의 오른쪽 자식 노드일 경우
    else if(x == x->parent->right){
        // x의 부모 노드의 오른쪽 자식 노드를 y로 변경
        x->parent->right = y;
    }
    // x가 x의 부모 노드의 왼쪽 자식 노드이면
    else{
        // x의 부모 노드의 왼쪽 자식 노드를 y로 변경
        x->parent->left = y;
    }

    // y의 오른쪽 자식 노드를 x로 변경
    y->right = x;
    // x의 부모 노드를 y로 변경
    x->parent = y;
}