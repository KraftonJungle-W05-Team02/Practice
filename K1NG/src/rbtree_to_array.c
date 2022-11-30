#include "rbtree.h"

int* traverse_to_arry(const rbtree* t, node_t* node, int* arr, int* pa, const size_t n)
{
  if (node != t->nil) {
		if (node->left != t->nil)
			arr = traverse_to_arry(t, node->left, arr, pa, n);
		if (arr - pa >= n) return;
		*arr = node->key;
		arr++;
		if (node->right != t->nil)
			arr = traverse_to_arry(t, node->right, arr, pa, n);
	}
  return arr;
}

int rbtree_to_array(const rbtree* t, key_t* arr, const size_t n)
{
  node_t* p = t->root;
	if (p == t->nil) return 0;
	traverse_to_arry(t, p, arr, arr, n);
	
	return 1;
}