#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

struct bst_node {
    struct bst_node *left, *right;
    int value;
};

struct bst {
    struct bst_node *root;
    unsigned int count;
};

#define _bst_node_new()	calloc(1, sizeof(struct bst_node))

static void 
_bst_node_delete(struct bst_node *node) {
    if (node->left)
        _bst_node_delete(node->left);
    if (node->right)
        _bst_node_delete(node->right);
    free(node);
}

struct bst * 
bst_new(void) {
    return calloc(1, sizeof(struct bst));
}

void 
bst_delete(struct bst *bst) {
    if (bst->root)
        _bst_node_delete(bst->root);
    free(bst);
}

static struct bst_node *  
_bst_node_search(struct bst *bst, int value, struct bst_node ***parent) {
    struct bst_node *node = bst->root;

    for (*parent = &bst->root; node; node = **parent) {
        if (value == node->value)
            return node;
        if (value < node->value)
            *parent = &node->left;
        else if (value > node->value)
            *parent = &node->right;
    }
    return NULL;
}

int 
bst_search(struct bst *bst, int value) {
    struct bst_node **parent = NULL;
    return _bst_node_search(bst, value, &parent) ? 0 : -1;
}

int 
bst_insert(struct bst *bst, int value) {
    struct bst_node *node = bst->root;
    struct bst_node **parent = &bst->root;

    while (node) {
        if (value < node->value)
            parent = &node->left;
        else if (value > node->value)
            parent = &node->right;
        else
            return 0;
        node = *parent;
    }

    if ((*parent = _bst_node_new()))
        (*parent)->value = value;
    else
        return -1;
    bst->count++;
    return 0;
}

int 
bst_remove(struct bst *bst, int value) {
    struct bst_node **parent;
	struct bst_node *node = _bst_node_search(bst, value, &parent);
   
    if (!node)
        return -1;

    if (!node->left && !node->right)
        *parent = NULL;
    else if (!node->left || !node->right)
        *parent = node->left ? node->left : node->right;
    else {
        /* right tree, min node */
        struct bst_node *min = node->right;
        struct bst_node **min_parent = &node->right;

        while (min->left) {
            min_parent = &min->left;
            min = min->left;
        }

        /* min remove from origin */
        *min_parent = min->right;
        min->left = node->left;
        min->right = node->right;
        /* min insert to node's parent */
        *parent = min;
    }

    free(node);
    bst->count--;
    return 0;
}

int 
bst_max(struct bst *bst) {
    struct bst_node *node = bst->root;

    if (node) {
    	while (node->right)
            node = node->right;
        return node->value;
    }
    return 0;
}

int 
bst_min(struct bst *bst) {
    struct bst_node *node = bst->root;

    if (node) {
    	while (node->left)
            node = node->left;
        return node->value;
    }
    return 0;
}

static void 
_bst_node_dump(struct bst_node *node) {
    if (node->left)
        _bst_node_dump(node->left);
    printf("%d\n", node->value);
    if (node->right)
        _bst_node_dump(node->right);
}

/* depth in-order */
void 
bst_dump(struct bst *bst) {
    printf("total %d nodes.\n\n", bst->count);
    _bst_node_dump(bst->root);
}

void bst_breadth_dump(struct bst *bst);
