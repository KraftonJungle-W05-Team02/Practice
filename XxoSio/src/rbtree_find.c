#include "rbtree.h"

node_t *rbtree_find(const rbtree *t, const key_t key){
    // 이동하면서 탐색할 노드 선언
    node_t *tmp = t->root;

    // nil까지 가거나, 찾고자하는 key를 찾으면 종료
    while(tmp != t->nil && tmp->key != key) { 
        // 찾을 키값보다 지금 위치의 키값이 더 크면
        if (tmp->key > key) {
            // 더 작은 값을 찾아야하니까 왼쪽 자식으로 이동
            tmp = tmp->left;
        }
        // 찾을 키값보다 지금 위치의 키값이 더 작으면
        else{
            // 더 큰 값을 찾아야 하니까 오른쪽 자식으로 이동
            tmp = tmp->right;
        }
    }
    
    // 키값이 같을 때
    if (tmp->key == key){
        //  temp 반환
        return tmp;
    }

    // 키값이 없을때 NULL 반환
    return NULL;
}