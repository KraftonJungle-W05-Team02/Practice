#include "rbtree.h"

node_t *left_rotate(rbtree *t, node_t *x) {
    // TODO: implement insert

    // x의 오른쪽 자식노드인 y를 설정
    node_t *y = x->right;
    // x의 오른쪽 자식을 y의 왼쪽 자식 노드로 변경 
    x->right = y->left;
    
    // y의 왼쪽 자식 노드가 nil 노드가 아닐 경우
    if(y->left != t->nil){
        // y의 왼쪽 자식 노드의 부모를 x로 변경
        y->left->parent = x;
    }

    // y의 부모 노드를 x의 부모 노드로 변경
    y->parent = x->parent;

    // x의 부모 노드가 nil 노드일 경우
    if(x->parent == t->nil){
        // 트리의 루트를 y로 변경
        t->root = y;
    }
    // x가 x의 부모의 왼쪽 자식일 경우
    else if(x == x->parent->left){
        // x의 부모 노드의 왼쪽 자식 노드를 y로 변경
        x->parent->left = y;
    }
	// x가 x의 부모 노드의 오른쪽 자식 노드이면
    else{
        // x의 부모 노드의 오른쪽 자식 노드를 y로 변경
        x->parent->right = y;
    }

    // y의 왼쪽 자식을 x로 변경
    y->left = x;
    // x의 부모 노드를 y로 변경
    x->parent = y;
}