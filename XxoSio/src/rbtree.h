#ifndef _RBTREE_H_
#define _RBTREE_H_

#define SENTINEL

#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

// color 집합 - RBTREE_RED = 0 / RBTREE_BLACK = 1
typedef enum { RBTREE_RED, RBTREE_BLACK } color_t;

// int 별칭(key_t) 생성
typedef int key_t;

// 노드 구조체
typedef struct node_t {
  color_t color;
  key_t key;
  struct node_t *parent, *left, *right;
} node_t;

// 트리 구조체
typedef struct {
  node_t *root;
  node_t *nil;  // for sentinel
} rbtree;

// 새로운 트리 생성(트리 초기화)
rbtree *new_rbtree(void);

// 트리에 새로운 노드 삽입
node_t *rbtree_insert(rbtree *, const key_t);
// 삽입된 노드를 rbtree 규칙에 맞도록 수정
node_t *rbtree_insert_fixup(rbtree *, node_t *);
// 이진 탐색 트리의 특성을 유지하며 노드 회전
node_t *left_rotate(rbtree *, node_t *);
node_t *right_rotate(rbtree *, node_t *);

// tree내의 key 탐색
node_t *rbtree_find(const rbtree *, const key_t);
// RB Tree 중 최소값 탐색
node_t *rbtree_min(const rbtree *);
// RB Tree 중 최대값 탐색
node_t *rbtree_max(const rbtree *);
// node_t *rbtree_successor(const rbtree *, node_t *);

// RB Tree의 내용을 key 순서대로 주어진 array 반환
int rbtree_to_array(const rbtree *, key_t *, const size_t);

// 한개의 노드를 삭제
int rbtree_erase(rbtree *, node_t *);
// 노드를 삭제후 RBTree 규칙에 맞도록 수정
void rbtree_erase_fixup(rbtree *, node_t *);

// 트리 전체를 삭제
void delete_rbtree(rbtree *);

#endif  // _RBTREE_H_