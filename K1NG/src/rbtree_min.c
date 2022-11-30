#include "rbtree.h"

node_t *rbtree_min(const rbtree *t)
{
  node_t *root = t->root;
  if (root == t->nil)
      return NULL;
  while (1)
  {
      if (root->left == t->nil) break;
      root = root->left;
  }
  return root;
}