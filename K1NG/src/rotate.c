#include "rotate.h"

void left_rotate(rbtree *t, node_t *rotating_node)
{
  // y = right[x] != NIL이 아니라고 가정해야한다!!
  if (rotating_node->right == t->nil)
    return;

  node_t *right_node = rotating_node->right;
  rotating_node->right = right_node->left;
  if (right_node->left != t->nil)
  {
    right_node->left->parent = rotating_node;
  }
  right_node->parent = rotating_node->parent;

  // x가 루트노드였을 때,
  if (rotating_node->parent == t->nil)
  {
    t->root = right_node;
  }
  else if (rotating_node == rotating_node->parent->left)
  {
    rotating_node->parent->left = right_node;
  }
  else
  {
    rotating_node->parent->right = right_node;
  }
  right_node->left = rotating_node;
  rotating_node->parent = right_node;
}

void right_rotate(rbtree *t, node_t *rotating_node)
{
  if (rotating_node->left == t->nil)
    return;
  node_t *left_node = rotating_node->left;
  rotating_node->left = left_node->right;
  if (left_node->right != t->nil)
  {
    left_node->right->parent = rotating_node;
  }

  left_node->parent = rotating_node->parent;

  if (rotating_node->parent == t->nil)
  {
    t->root = left_node;
  }
  else if (rotating_node == rotating_node->parent->left)
  {
    rotating_node->parent->left = left_node;
  }
  else
  {
    rotating_node->parent->right = left_node;
  }
  left_node->right = rotating_node;
  rotating_node->parent = left_node;
}