#include "rbtree.h"

rbtree *new_rbtree(void) {
    rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
    // TODO: initialize struct if needed
    
    // NIL 노드 생성
    node_t *NIL = (node_t *)calloc(1, sizeof(node_t));

    // NIL 노드의 색을 Black으로 설정
    NIL->color = RBTREE_BLACK;

    // 트리의 nil을 NIL로 설정
    p->nil = NIL;
    // 트리의 루트 노드를 nill로 연결
    p->root = p->nil;
    
    // 트리 반환
    return p;
}