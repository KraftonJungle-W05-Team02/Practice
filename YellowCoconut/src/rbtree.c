#include "rbtree.h"

#include <stdlib.h>
#define SENTINEL

int i;

node_t *new_node(rbtree *t, const key_t key)
{
    node_t *x = (node_t *)calloc(1, sizeof(node_t));
    x->left = t->nil;
    x->right = t->nil;
    x->parent = t->nil;
    x->key = key;
    x->color = RBTREE_RED;

    return x;
}

rbtree *new_rbtree(void)
{
    rbtree *t = (rbtree *)calloc(1, sizeof(rbtree));
    node_t *nil_node = (node_t *)calloc(1, sizeof(node_t));

    nil_node->left = NULL;
    nil_node->right = NULL;
    nil_node->parent = NULL;
    nil_node->key = 0;
    nil_node->color = RBTREE_BLACK;

    t->nil = nil_node;
    t->root = t->nil;

    // TODO: initialize struct if needed
    return t;
}

void free_rbtree(node_t *root, node_t *nil)
{
    if (root == nil)
        return;
    free_rbtree(root->left, nil);
    free_rbtree(root->right, nil);
    free(root);
}

void delete_rbtree(rbtree *t)
{
    free_rbtree(t->root, t->nil);
    free(t->nil);
    free(t);
    // TODO: reclaim the tree nodes's memory
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{
    node_t *y = t->nil;
    node_t *x = t->root;
    node_t *z = new_node(t, key);
    while (x != t->nil)
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == t->nil)
        t->root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
    z->left = t->nil;
    z->right = t->nil;
    z->color = RBTREE_RED;
    rbtree_insert_fixup(t, z);

    // TODO: implement insert
    return z;
}

void left_rotate(rbtree *t, node_t *x)
{
    node_t *y = x->right;
    x->right = y->left;
    if (y->left != t->nil)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == t->nil)
    {
        t->root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void right_rotate(rbtree *t, node_t *y)
{
    node_t *x = y->left;
    y->left = x->right;
    if (x->right != t->nil)
    {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == t->nil)
    {
        t->root = x;
    }
    else if (y == y->parent->left)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

void rbtree_insert_fixup(rbtree *t, node_t *z)
{
    node_t *y;
    while (z->parent->color == RBTREE_RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            y = z->parent->parent->right;
            if (y->color == RBTREE_RED)
            {
                z->parent->color = RBTREE_BLACK;
                y->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                z = z->parent->parent;
            }
            else if (z == z->parent->right)
            {
                z = z->parent;
                left_rotate(t, z);
                z->parent->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                right_rotate(t, z->parent->parent);
            }
            else
            {
                z->parent->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                right_rotate(t, z->parent->parent);
            }
        }
        else
        {
            y = z->parent->parent->left;
            if (y->color == RBTREE_RED)
            {
                z->parent->color = RBTREE_BLACK;
                y->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                z = z->parent->parent;
            }
            else if (z == z->parent->left)
            {
                z = z->parent;
                right_rotate(t, z);
                z->parent->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                left_rotate(t, z->parent->parent);
            }
            else
            {
                z->parent->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                left_rotate(t, z->parent->parent);
            }
        }
    }
    t->root->color = RBTREE_BLACK;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
    // TODO: implement find
    node_t *now = t->root;
    while (key != now->key && now->key != 0)
    {
        if (now->key > key)
            now = now->left;
        else
            now = now->right;
    }

    if (key == now->key)
        return now;
    else
        return NULL;
}

node_t *rbtree_min(const rbtree *t)
{
    // TODO: implement find
    node_t *now = t->root;
    while (now->left != t->nil)
    {
        now = now->left;
    }
    return now;
}

node_t *rbtree_max(const rbtree *t)
{
    node_t *now = t->root;
    while (now->right != t->nil)
    {
        now = now->right;
    }
    // TODO: implement find
    return now;
}

node_t *rbtree_successor(rbtree *t, node_t *z)
{
    node_t *y;
    if (z->right != t->nil)
    {
        node_t *now = z->right;
        if (now == t->nil)
        {
            return t->nil;
        }
        while (now->left != t->nil)
        {
            now = now->left;
        }
        return now;
    }
    y = z->parent;
    while (y != t->nil && z == y->right)
    {
        z = y;
        y = y->parent;
    }
    return y;
}

void rbtree_erase_fixup(rbtree *t, node_t *x)
{
    node_t *w;
    while (x != t->root && x->color == RBTREE_BLACK)
    {
        if (x == x->parent->left)
        {
            w = x->parent->right;
            if (w->color == RBTREE_RED)
            {
                w->color = RBTREE_BLACK;
                x->parent->color = RBTREE_RED;
                left_rotate(t, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK)
            {
                w->color = RBTREE_RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == RBTREE_BLACK)
                {
                    w->left->color = RBTREE_BLACK;
                    w->color = RBTREE_RED;
                    right_rotate(t, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = RBTREE_BLACK;
                w->right->color = RBTREE_BLACK;
                left_rotate(t, x->parent);
                x = t->root;
            }
        }
        else
        {
            w = x->parent->left;
            if (w->color == RBTREE_RED)
            {
                w->color = RBTREE_BLACK;
                x->parent->color = RBTREE_RED;
                right_rotate(t, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK)
            {
                w->color = RBTREE_RED;
                x = x->parent;
            }
            else
            {
                if (w->left->color == RBTREE_BLACK)
                {
                    w->right->color = RBTREE_BLACK;
                    w->color = RBTREE_RED;
                    left_rotate(t, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = RBTREE_BLACK;
                w->left->color = RBTREE_BLACK;
                right_rotate(t, x->parent);
                x = t->root;
            }
        }
    }
    x->color = RBTREE_BLACK;
}

int rbtree_erase(rbtree *t, node_t *z)
{
    node_t *y;
    node_t *x;
    if (z->left == t->nil || z->right == t->nil)
        y = z;
    else
        y = rbtree_successor(t, z);
    if (y->left != t->nil)
    {
        x = y->left;
    }
    else
        x = y->right;
    x->parent = y->parent;
    if (y->parent == t->nil)
    {
        t->root = x;
    }
    else if (y == y->parent->left)
    {
        y->parent->left = x;
    }
    else
        y->parent->right = x;
    if (y != z)
    {
        z->key = y->key;
    }
    if (y->color == RBTREE_BLACK)
    {
        rbtree_erase_fixup(t, x);
    }
    free(y);
    // TODO: implement erase
    return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
    // TODO: implement to_array
    i = 0;

    inorder_trav(t->root, t->nil, arr, n);
    return 0;
}

void inorder_trav(node_t *root, node_t *nil, key_t *arr, const size_t n)
{
    if (root == nil || i == n)
        return;
    if (root != nil)
    {
        inorder_trav(root->left, nil, arr, n);
        arr[i++] = root->key;
        inorder_trav(root->right, nil, arr, n);
    }
    return;
}