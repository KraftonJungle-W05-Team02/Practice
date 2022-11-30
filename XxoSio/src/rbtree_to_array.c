#include "rbtree.h"

int inorder_array(const rbtree *t, node_t *p, key_t *arr, int i);

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
    // TODO: implement to_array

    // 이동하면서 검사항 노드 tmp 선언
    // tmp는 루트에서부터 시작
    node_t *tmp = t->root;    
    
    // 중위 순회를 돌면서 순서대로 정렬
    inorder_array(t, tmp, arr, 0);
    
    return 0;
}

int inorder_array(const rbtree *t, node_t *p, key_t *arr, int i){
    // 찾는 P가 nil일 경우
    if(p == t->nil){
        // i값 리턴
        return i;
    }

    //   80
    //  /  \
    // 40  120
    // 작은 값 중위 순회
    i = inorder_array(t, p->left, arr, i);
    // 배열을 하나씩 늘려가며 key값 저장
    // 오름차순으로 정렬해야 하므로 left를 먼저 하고 값을 저장
    // 40, 80, 120 순으로 나와야함
    arr[i++] = p->key;
    // 큰 값 중위 순회
    i = inorder_array(t, p->right, arr, i);

    // i값 리턴
    return i;
}