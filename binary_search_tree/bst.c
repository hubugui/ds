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
	return calloc(1, sizeof(struct bst))
}

void 
bst_delete(struct bst *bst) {
	if (bst->root)
		_bst_node_delete(bst->root);
	free(bst);
}

static struct bst_node *  
_bst_node_find(struct bst *bst, int value, struct bst_node **parent, char *left_child) {
	struct bst_node *node = bst->root;

    *parent = NULL;
	while (node) {
        if (value == node->value)
            return node;
        *parent = node;
		if (value < node->value) {
			node = node->left;
            *left_child = 1;
        } else if (value > node->value) {
			node = node->right;
            *left_child = 0;
        }
	}
	return NULL;
}

int 
bst_find(struct bst *bst, int value) {
    struct bst_node *parent = NULL;
    char left_child = 0;

    return _bst_node_find(bst, value, &parent, &left_child) ? 0 : -1;
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
        node = *parent;
		return 0;
	}

    if (*parent = _bst_node_new())
        (*parent)->value = value;
    else
        return -1;
	return 0;
}

int 
bst_remove(struct bst *bst, int value) {
    struct bst_node *parent = NULL;
    char left_child = 0;
	struct bst_node *node = _bst_node_find(bst, value, &parent, &left_child) ? 0 : -1;
   
    if (!node)
        return -1;

    if (!node->left && !node->right) {
        if (parent) {
            if (left_child)
                parent->left = NULL;
            else
                parent->right = NULL;
        } else
            bst->root = NULL;
    } else if (!node->left || !node->right) {
       if (parent) {
            if (left_child)
                parent->left = node->left ? node->left : node->right;
            else
                parent->right = node->left ? node->left : node->right;
       } else
            bst->root = node->left ? node->left : node->right;
    } else {
        
    }

    free(node);
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
