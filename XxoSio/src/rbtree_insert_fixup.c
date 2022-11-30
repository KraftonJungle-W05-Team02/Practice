#include "rbtree.h"

node_t *rbtree_insert_fixup(rbtree *t, node_t *z) {
    // TODO: implement insert

    // z의 부모 노드가 붉은색인 경우
    while(z->parent->color== RBTREE_RED){
        // z의 부모 노드가 왼쪽 자식 노드인 경우
        // => z의 부모 노드가 z의 조부모의 왼쪽 자식인 경우
        if(z->parent == z->parent->parent->left){
            // z의 오른쪽 삼촌 y 노드 선언
            node_t *y = z->parent->parent->right;

            // 경우1 : z의 삼촌 y가 레드
            // y(삼촌) 노드가 붉은색인 경우
            if(y->color == RBTREE_RED){
                // z의 부모 노드 색상을 흑색으로 변경
                z->parent->color = RBTREE_BLACK;
                // y(삼촌) 노드의 색상을 흑색으로 변경
                y->color = RBTREE_BLACK;
                // z의 부모의 부모의 색상을 붉은색으로 변경
                // => z의 조부모의 색상을 붉은색으로 변경
                z->parent->parent->color = RBTREE_RED;
                // z를 z의 조부모로 노드 변경
                z = z->parent->parent;
            }
            else{ 
                // 경우2 : z의 삼촌 y가 흑색이며 z가 오른쪽 자식인 경우
                // z가 z의 부모의 오른쪽 노드인 경우
                if(z == z->parent->right){
                    // z를 z의 부모로 변경
                    z = z->parent;
                    // z를 중심으로 왼쪽으로 회전
                    left_rotate(t, z);
                }

                // 경우3 : z의 삼촌 y가 흑색이며 z가 왼쪽 자식인 경우
                // z의 부모의 색상을 흑색으로 변경
                z->parent->color = RBTREE_BLACK;
                // z의 조부모의 색상을 붉은색으로 변경
                z->parent->parent->color = RBTREE_RED;
                
                // z의 조부모를 중심으로 오른쪽 회전
                right_rotate(t, z->parent->parent);
            }
        }
        // z의 부모 노드가 오른쪽 자식 노드인 경우
        // => z의 부모 노드가 z의 조부모의 오른쪽 자식인 경우
        else{
            // z의 왼쪽 삼촌노드 y 노드 선언
            node_t *y = z->parent->parent->left;

            // 경우1 : z의 삼촌 y가 레드
            // y(삼촌) 노드가 붉은색인 경우
            if(y->color == RBTREE_RED){
                // z의 부모의 색상을 흑색으로 변경
                z->parent->color = RBTREE_BLACK;
                // y의 색상을 흑색으로 변경
                y->color = RBTREE_BLACK;
                // z의 조부모의 색상을 붉은색으로 변경
                z->parent->parent->color = RBTREE_RED;
                // z를 z의 조부모로 변경
                z = z->parent->parent;
            }
            else{
                // 경우2 : z의 삼촌 y가 흑색이며 z가 왼쪽 자식인 경우
                // z가 z의 부모의 왼쪽 노드인 경우
                if(z == z->parent->left){
                    // z를 z의 부모로 변경
                    z = z->parent;
                    // z를 중심으로 오른쪽 회전
                    right_rotate(t, z);
                }

                // 경우3 : z의 삼촌 y가 흑색이며 z가 오른쪽 자식인 경우
                // z의 부모의 색상을 흑색으로 변경
                z->parent->color = RBTREE_BLACK;
                // z의 조부모의 색상을 붉은색으로 변경
                z->parent->parent->color = RBTREE_RED;
                // z의 조부모를 중심으로 왼쪽 회전
                left_rotate(t, z->parent->parent);
            }
        }
    }

    // 트리의 루트 노드롤 검은 노드로 변경
    t->root->color = RBTREE_BLACK;
}