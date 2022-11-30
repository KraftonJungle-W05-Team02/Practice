#include "rbtree.h"

rbtree *new_rbtree(void)
{
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));

  node_t *nil_node = (node_t *)malloc(sizeof(node_t));
  nil_node->color = RBTREE_BLACK;

  p->nil = nil_node;
  p->root = p->nil;
  return p;
}
