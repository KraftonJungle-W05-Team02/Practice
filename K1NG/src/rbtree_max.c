#include "rbtree.h"

node_t *rbtree_max(const rbtree *t)
{
  node_t *root = t->root;
  if (root == t->nil)
      return NULL;

    while (1)
  {
    if (root->right == t->nil) break;
    root = root->right;
  }
  return root;
}