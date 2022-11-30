#include "rbtree.h"
#include "rotate.h"

void rb_insert_fixup(rbtree *, node_t *);
node_t *new_node(const key_t);

node_t *rbtree_insert(rbtree *t, const key_t key)
{
  // 새 노드 생성
  node_t *new_node = make_node(t, key);
  node_t *tracker = t->nil;
  node_t *pointer = t->root;

  while (pointer != t->nil)
  {
    // y자리에 새 노드가 들어갈 예정
    tracker = pointer;

    if (new_node->key < pointer->key)
      pointer = pointer->left;
    else
      pointer = pointer->right;
  }

  new_node->parent = tracker;

  // 빈 트리일 경우
  if (tracker == t->nil)
    t->root = new_node;

  else if (tracker->key > new_node->key)
    tracker->left = new_node;
  else
    tracker->right = new_node;

  new_node->left = t->nil;
  new_node->right = t->nil;
  new_node->color = RBTREE_RED;

  // Red - Red 위반이 일어났을 경우 조정이 필요.
  rb_insert_fixup(t, new_node);
  return t->root;
}

node_t *make_node(rbtree *t, const key_t key)
{
  node_t *new_node = (node_t *)malloc(sizeof(node_t));

  new_node->color = RBTREE_RED;
  new_node->key = key;

  return new_node;
}

void rb_insert_fixup(rbtree *t, node_t *fix_node)
{

  // 6가지 케이스를 주의하면서 Red, Red 위반을 조정한다.
  node_t *uncle_node = NULL;
  while (fix_node->parent->color == RBTREE_RED)
  {
    // 부모가 조상의 왼쪽 자식일 때 case 1, 2, 3
    if (fix_node->parent == fix_node->parent->parent->left)
    {

      uncle_node = fix_node->parent->parent->right;

      // case 1
      if (uncle_node->color == RBTREE_RED)
      {

        fix_node->parent->color = RBTREE_BLACK;
        uncle_node->color = RBTREE_BLACK;
        fix_node->parent->parent->color = RBTREE_RED;
        fix_node = fix_node->parent->parent;

      } 
      else
      {
        // case 2
        if (fix_node == fix_node->parent->right)
        {
          fix_node = fix_node->parent;
          left_rotate(t, fix_node);
        }
        // case 3
        fix_node->parent->color = RBTREE_BLACK;
        fix_node->parent->parent->color = RBTREE_RED;  
        right_rotate(t, fix_node->parent->parent);

      }
    }
    else
    {
      // case  4, 5, 6
      uncle_node = fix_node->parent->parent->left;

      // case 4
      if (uncle_node->color == RBTREE_RED)
      {

        fix_node->parent->color = RBTREE_BLACK;
        uncle_node->color = RBTREE_BLACK;
        fix_node->parent->parent->color = RBTREE_RED;
        fix_node = fix_node->parent->parent;

      } // case 5인경우 case 6로 만들어주면 끝
      else
      {
        if (fix_node == fix_node->parent->left)
        {
          fix_node = fix_node->parent;
          right_rotate(t, fix_node);
        }
        
        fix_node->parent->color = RBTREE_BLACK;
        fix_node->parent->parent->color = RBTREE_RED;
        left_rotate(t, fix_node->parent->parent);
      } 
    }
  }
  t->root->color = RBTREE_BLACK;
}
