#include "rbtree.h"

node_t *rbtree_min(const rbtree *t) {
    // TODO: implement find

    // 이동하면서 탐색할 노드 선언
    node_t *tmp = t->root;

    // nil까지 계속 탐색
    while(tmp->left != t->nil) { 
        // min을 찾아야 하므로 계속해서 왼쪽 자식으로 이동
        tmp = tmp->left;
    }

    // min의 노드 반환
    return tmp;
}