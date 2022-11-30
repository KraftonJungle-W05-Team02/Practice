#include "rbtree.h"

/*
  못찾으면 NULL, 루트여도 NULL을 반환.
  찾으면 해당 키의 노드를 반환.
*/
node_t *rbtree_find(const rbtree *t, const key_t key)
{
  node_t *root = t->root;
  
  if (root == t->nil)
    return NULL;

  while (root != t->nil)
  {
    if (root->key == key)
      return root;

    if (root->key > key)
      root = root->left;
    else if (root->key <= key)
      root = root->right;
  }
  return NULL;
}