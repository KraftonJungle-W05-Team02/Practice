#include "rbtree.h"

void rbtree_erase_fixup(rbtree *t, node_t *x) {
    node_t *w;
    while(x != t->root && x->color == RBTREE_BLACK){
        if(x == x->parent->left){
            w = x->parent->right;

            // case1 
            if(w->color == RBTREE_RED){
                w->color = RBTREE_BLACK;
                x->parent->color = RBTREE_RED;
                 
                left_rotate(t, x->parent);
                
                w = x->parent->right;
            }
            // case2
            if(w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK){
                w->color = RBTREE_RED;
                x = x->parent;
            }
            // case3
            else{
                if(w->right->color == RBTREE_BLACK){
                    w->left->color = RBTREE_BLACK;
                    w->color = RBTREE_RED;

                    right_rotate(t, w);

                    w = x->parent->right;
                }

                // case4
                w->color = x->parent->color;
                x->parent->color = RBTREE_BLACK;
                w->right->color = RBTREE_BLACK;

                left_rotate(t, x->parent);

                x = t->root;
            }
        }
        else{
            w = x->parent->left;

            if(w->color == RBTREE_RED){
                w->color = RBTREE_BLACK;
                x->parent->color = RBTREE_RED;

                right_rotate(t, x->parent);

                w = x->parent->left;
            }
            
            if(w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK){
                    w->color = RBTREE_RED;
                    x = x->parent;
            }
            else{
                if(w->left->color == RBTREE_BLACK){
                    w->right->color = RBTREE_BLACK;
                    w->color = RBTREE_RED;

                    left_rotate(t, w);

                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = RBTREE_BLACK;
                w->left->color = RBTREE_BLACK;

                right_rotate(t, x->parent);
                
                x = t->root;
            }
        }
    }

    x->color = RBTREE_BLACK;
}

// void rbtree_erase_fixup(rbtree *t, node_t *x) {
//   node_t *target = x;
//   while ((target!= t->root) && (target->color == RBTREE_BLACK)) {
//     if (target == target->parent->left) {
//       node_t *w = target->parent->right;
//       if (w->color == RBTREE_RED) {
//         w->color = RBTREE_BLACK;
//         target->parent->color = RBTREE_RED;
//         left_rotate(t, target->parent);
//         w = target->parent->right;
//       }
//       if ((w->left->color == RBTREE_BLACK) && (w->right->color == RBTREE_BLACK)) {
//         w->color = RBTREE_RED;
//         target = target->parent;
//       }
//       else {
//         if (w->right->color == RBTREE_BLACK) {
//           w->left->color = RBTREE_BLACK;
//           w->color = RBTREE_RED;
//           right_rotate(t, w);
//           w = target->parent->right;
//         }
//         w->color = target->parent->color;
//         target->parent->color = RBTREE_BLACK;
//         w->right->color = RBTREE_BLACK;
//         left_rotate(t, target->parent);
//         target = t->root;
//       }
//     }
//     else {
//       node_t *w = target->parent->left;
//       if (w->color == RBTREE_RED) {
//         w->color = RBTREE_BLACK;
//         target->parent->color = RBTREE_RED;
//         right_rotate(t, target->parent);
//         w = target->parent->left;
//       }
//       if ((w->left->color == RBTREE_BLACK) && (w->right->color == RBTREE_BLACK)) {
//         w->color = RBTREE_RED;
//         target = target->parent;
//       }
//       else {
//         if (w->left->color == RBTREE_BLACK) {
//           w->right->color = RBTREE_BLACK;
//           w->color = RBTREE_RED;
//           left_rotate(t, w);
//           w = target->parent->left;
//         }
//         w->color = target->parent->color;
//         target->parent->color = RBTREE_BLACK;
//         w->left->color = RBTREE_BLACK;
//         right_rotate(t, target->parent);
//         target = t->root;
//       }
//     }
//   }
//   target->color = RBTREE_BLACK;
// }