#include "rbtree.h"

void rbtree_transplant(rbtree *t, node_t *u, node_t *v);

int rbtree_erase(rbtree *t, node_t *z) {
    // TODO: implement erase

    // 노드 z를 복사한 y 선언
    node_t *y = z;
    // y의 색상 저장
    color_t y_original_color = y->color;

    // 노드 x 선언
    node_t *x;
    // z의 왼쪽 자식이 nil일 경우
    if(z->left == t->nil){
        // x를 z의 오른쪽 자식 노드로 변경
        x = z->right;
        // z의 부모 노드와 z의 오른쪽 자식 노드의 연결 관계 생성
        rbtree_transplant(t, z, z->right);
    }
    // z의 오른쪽 자식 노드가 nil일 경우
    else if(z->right == t->nil){
        // x를 z의 왼쪽 자식으로 변경
        x = z->left;
        // z의 부모 노드와 z의 왼쪽 자식 노드의 연결 관계 생성
        rbtree_transplant(t, z, z->left);
    }
    // z의 양 자식 노드가 전부 존재할 경우
    else{
        // y를 z의 오른쪽 자식 노드로 변경
        y = z->right;

        // y의 왼쪽 자식 노드가 nil이 아닌 경우
        while(y->left != t->nil){
            // y를 y의 왼쪽 자식 노드로 변경
            y = y->left;
        }
        // y의 색상 저장
        y_original_color = y->color;
        // x를 y의 오른쪽 자식 노드로 변경
        x = y->right;

        // y가 z의 오른쪽 자식 노드가 아닌 경우
        if(y != z->right){
            // y의 부모 노드와 y의 오른쪽 자식 노드의 연결 관계 생성
            rbtree_transplant(t, y, y->right);

            // y의 오른쪽 자식 노드를 z의 오른쪽 자식 노드로 변경
            y->right = z->right;
            // y의 오른쪽 자식 노드의 부모를 y로 변경
            y->right->parent = y;
        }
        // x가 nil일 경우
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
    z = NULL;

    return 0;
}

void rbtree_transplant(rbtree *t, node_t *u, node_t *v){
    // u의 부모가 nil(root)이 아닌경우
    if(u->parent == t->nil){
        // 루트 노드를 v로 변경
        t->root = v;
    }
    // u가 u의 부모의 왼쪽 자식인 경우
    else if(u == u->parent->left){
        // u의 부모의 왼쪽 자식을 v로 변경
        u->parent->left = v;
    }
    // u가 u의 부모의 오른족 자식인 경우
    else{
        // u의 부모의 오른쪽 자식을 v로 변경
        u->parent->right = v;
    }

    // v의 부모 노드를 u의 부모 노드로 변경
    v->parent = u->parent;
}

// node_t *find_successor(rbtree *t, node_t *p) {
//   while (p->left != t->nil) {
//     p = p->left;
//   }
//   return p;  
// }

// void transplant(rbtree *t, node_t *u, node_t *v) {
//   if (u->parent == t->nil) t->root = v;
//   else if (u == u->parent->left) u->parent->left = v;
//   else u->parent->right = v;
//   v->parent = u->parent;
// }

// int rbtree_erase(rbtree *t, node_t *p) {
//   node_t *y = p;
//   node_t *x;
//   color_t y_original_color = y->color;
//   if (p->left == t->nil) {
//     x = p->right;
//     transplant(t, p, p->right);
//   }
//   else if (p->right == t->nil) {
//     x = p->left;
//     transplant(t, p, p->left);
//   }
//   else {
//     y = find_successor(t, p->right);
//     y_original_color = y->color;
//     x = y->right;
//     if (y->parent == p) x->parent = y;
//     else {
//       transplant(t, y, y->right);
//       y->right = p->right;
//       y->right->parent = y;
//     }
//     transplant(t, p, y);
//     y->left = p->left;
//     y->left->parent = y;
//     y->color = p->color;
//   }
//   if (y_original_color == RBTREE_BLACK) {
//     rbtree_erase_fixup(t, x);
//   }
//   free(p);
//   return 0;
// }
