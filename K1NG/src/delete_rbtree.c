#include "rbtree.h"

void post_order(rbtree*, node_t*);

void delete_rbtree(rbtree * rb)
{
  post_order(rb, rb->root);
  free(rb->nil);
  free(rb);
}

void post_order(rbtree* rb, node_t* root)
{ 
  if (root == rb->nil) return;
  post_order(rb, root->left);
  post_order(rb, root->right);
  free(root);
}
