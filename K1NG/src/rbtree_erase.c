#include "rbtree.h"
#include "rotate.h"

void rb_transplant(rbtree *, node_t *, node_t *);
node_t *min_subtree_node(rbtree *, node_t *);
void rb_delete_fixup(rbtree *, node_t *);
/*
  삭제 3가지 경우
  1. 삭제 노드의 왼쪽 자식이 NIL
  2. 삭제 노드의 오른쪽 자식이 NIL
  3. 삭제 노드의 자식들이 NIL이 아닐 때
*/

int rbtree_erase(rbtree *t, node_t *erase_node)
{
  node_t *tracker;
  // 자식이 1 이하 일 경우
  node_t *cursor = erase_node;
  color_t original_color = cursor->color;

  if (erase_node->left == t->nil)
  {
    tracker = erase_node->right;
    rb_transplant(t, erase_node, erase_node->right);
  }

  else if (erase_node->right == t->nil)
  {
    tracker = erase_node->left;
    rb_transplant(t, erase_node, erase_node->left);
  }

  else
  {
    cursor = min_subtree_node(t, erase_node->right);
    original_color = cursor->color;
    tracker = cursor->right;

    if (cursor->parent == erase_node)
      tracker->parent = cursor;
    else
    {
      rb_transplant(t, cursor, cursor->right);
      cursor->right = erase_node->right;
      cursor->right->parent = cursor;
    }

    rb_transplant(t, erase_node, cursor);
    cursor->left = erase_node->left;
    cursor->left->parent = cursor;
    cursor->color = erase_node->color;
  }

  // rbtree 규칙 5를 어기게 된다. => 조정 필요
  if (original_color == RBTREE_BLACK)
    rb_delete_fixup(t, tracker);
  free(erase_node);
}

/*
  서브트리를 옮김으로서 삭제를 수행
*/
void rb_transplant(rbtree *t, node_t *u, node_t *v)
{
  // u가 루트노드일 때
  if (u->parent == t->nil)
    t->root = v;

  // u가 부모의 왼쪽 자식일 때
  else if (u == u->parent->left)
    u->parent->left = v;

  // u가 부모의 오른쪽 자식일 때
  else
    u->parent->right = v;

  v->parent = u->parent;
}

/*
  삭제 함수에서 자기 오른쪽 서브트리의
  최소 노드를 찾는 함수
*/
node_t *min_subtree_node(rbtree *t, node_t *st)
{ 
  node_t* min_node = st;
  while (min_node->left != t->nil)
  {
    min_node = min_node->left;
  }  
  return min_node;
}

void rb_delete_fixup(rbtree *t, node_t *tracker)
{
  node_t *sibling;
  // 전달받은 노드의 색이 검정일 때 만 작업한다.
  while (tracker != t->root && tracker->color == RBTREE_BLACK)
  {
    if (tracker == tracker->parent->left)
    {
      sibling = tracker->parent->right;
      // case 1 형제노드 색이 빨강일 때
      if (sibling->color == RBTREE_RED)
      {
        sibling->color = RBTREE_BLACK;
        tracker->parent->color = RBTREE_RED;
        left_rotate(t, tracker->parent);
        sibling = tracker->parent->right;
      }
      // case 2 형제노드의 자식들의 색이 검정일 때 -> 일단은 규칙에 어긋난다.
      if (sibling->left->color == RBTREE_BLACK && sibling->right->color == RBTREE_BLACK)
      {
        sibling->color = RBTREE_RED;
        tracker = tracker->parent;
      }
      // case 3 형제노드의 오른쪽 자식이 검정일 때
      else
      {
        if (sibling->right->color == RBTREE_BLACK)
        {
          sibling->left->color = RBTREE_BLACK;
          sibling->color = RBTREE_RED;
          right_rotate(t, sibling);
          sibling = tracker->parent->right;
        }
        // case 3의 결과로 4가 만들어진다.
        // case 4 형제노드가 검정이고 형제노드의 오른쪽 자식이 빨강
        sibling->color = tracker->parent->color;
        tracker->parent->color = RBTREE_BLACK;
        sibling->right->color = RBTREE_BLACK;
        left_rotate(t, tracker->parent);
        // 해당 while문을 탈출하기 위해서 루트로 만들어줌.
        tracker = t->root;
      }
    }
    else
    {
      if (tracker == tracker->parent->right)
      {
        sibling = tracker->parent->left;
        // case 5 형제노드 색이 빨강일 때
        if (sibling->color == RBTREE_RED)
        {
          sibling->color = RBTREE_BLACK;
          tracker->parent->color = RBTREE_RED;
          right_rotate(t, tracker->parent);
          sibling = tracker->parent->left;
        }
        // case 6 형제노드의 자식들의 색이 검정일 때 -> 일단은 규칙에 어긋난다.
        if (sibling->right->color == RBTREE_BLACK && sibling->left->color == RBTREE_BLACK)
        {
          sibling->color = RBTREE_RED;
          tracker = tracker->parent;
        }
        // case 7 형제노드의 왼쪽 자식이 검정일 때
        else
        {
          if (sibling->left->color == RBTREE_BLACK)
          {
            sibling->right->color = RBTREE_BLACK;
            sibling->color = RBTREE_RED;
            left_rotate(t, sibling);
            sibling = tracker->parent->left;
          }
          // case 3의 결과로 4가 만들어진다.
          // case 4 형제노드가 검정이고 형제노드의 오른쪽 자식이 빨강
          sibling->color = tracker->parent->color;
          tracker->parent->color = RBTREE_BLACK;
          sibling->left->color = RBTREE_BLACK;
          right_rotate(t, tracker->parent);
          // 해당 while문을 탈출하기 위해서 루트로 만들어줌.
          tracker = t->root;
        }
      }
    }
  }
  tracker->color = RBTREE_BLACK;
}