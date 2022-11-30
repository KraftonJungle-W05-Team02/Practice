#include "rbtree.h"

node_t *rbtree_insert(rbtree *t, const key_t key) {
    // TODO: implement insert

    // 삽입할 노드 z 메모리 할당
    node_t *z = (node_t *)calloc(1, sizeof(node_t));
    // 트리의 nil 노드인 y 설정
    node_t *y = t->nil;
    // 트리의 루트 노드인 x 설정
    node_t *x = t->root;

    // z의 key를 입력받은 key로 변경
    z->key = key;

    // x 노드가 nil이 아니라면
    while(x != t->nil){
        // y는 x를 저장
        y = x;
        // z의 key가 y의 key보다 작으면
        if(z->key < y->key){
            // x에 x의 왼쪽 자식 노드 저장
            x = x->left;
        }
        // z의 key가 x의 key보다 크면
        else{
            // x에 x의 오른쪽 자식 노드에 저장
            x = x->right;
        }
    }

    // z의 부모 노드를 y로 변경
    z->parent = y;
    
    // y가 트리의 nil이면
    if(y == t->nil){
        // 트리의 루트 노드를 z로 변경
        t->root = z;
    }
    // z의 key가 y의 key보다 작으면
    else if(z->key < y->key){
        // y의 왼쪽 자식 노드를 z로 변경
        y->left = z;
    }
    // z의 key가 x의 key보다 크면
    else{
        // y의 오른쪽 자식을 z로 변경
        y->right = z;
    }

    // z의 왼쪽 자식 노드를 트리의 nil로 변경
    z->left = t->nil;
    // z의 오른쪽 자식 노드를 트리의 nil로 변경
    z->right = t->nil;
    // z의 색상을 RBTREE_RED로 변경
    z->color = RBTREE_RED;

    //RB Tree의 속성에 맞도록 수정하는 함수
    rbtree_insert_fixup(t, z);

    // 트리의 루트를 반환
    return t->root;
}