#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

struct avl_node {
    struct avl_node *left, *right;
    int value;
};

struct avl {
    struct avl_node *root;
    unsigned int count;
};

#define _avl_node_new()	calloc(1, sizeof(struct avl_node))

static void 
_avl_node_delete(struct avl_node *node) {
    if (node->left)
        _avl_node_delete(node->left);
    if (node->right)
        _avl_node_delete(node->right);
    free(node);
}

struct avl * 
avl_new(void) {
    return calloc(1, sizeof(struct avl));
}

void 
avl_delete(struct avl *avl) {
    if (avl->root)
        _avl_node_delete(avl->root);
    free(avl);
}

static struct avl_node *  
_avl_node_search(struct avl *avl, int value, struct avl_node ***parent) {
    struct avl_node *node = avl->root;

    for (*parent = &avl->root; node; node = **parent) {
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
avl_search(struct avl *avl, int value) {
    struct avl_node **parent = NULL;
    return _avl_node_search(avl, value, &parent) ? 0 : -1;
}

int 
avl_insert(struct avl *avl, int value) {
    struct avl_node *node = avl->root;
    struct avl_node **parent = &avl->root;

    while (node) {
        if (value < node->value)
            parent = &node->left;
        else if (value > node->value)
            parent = &node->right;
        else
            return 0;
        node = *parent;
    }

    if ((*parent = _avl_node_new()))
        (*parent)->value = value;
    else
        return -1;
    avl->count++;

    /* adjust */
    return 0;
}

int 
avl_remove(struct avl *avl, int value) {
    struct avl_node **parent;
	struct avl_node *node = _avl_node_search(avl, value, &parent);
   
    if (!node)
        return -1;

    if (!node->left && !node->right)
        *parent = NULL;
    else if (!node->left || !node->right)
        *parent = node->left ? node->left : node->right;
    else {
        /* right tree, min node */
        struct avl_node *min = node->right;
        struct avl_node **min_parent = &node->right;

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
    avl->count--;

    /* adjust */
    return 0;
}

int 
avl_max(struct avl *avl) {
    struct avl_node *node = avl->root;

    if (node) {
    	while (node->right)
            node = node->right;
        return node->value;
    }
    return 0;
}

int 
avl_min(struct avl *avl) {
    struct avl_node *node = avl->root;

    if (node) {
    	while (node->left)
            node = node->left;
        return node->value;
    }
    return 0;
}

static void 
_avl_node_dump(struct avl_node *node) {
    if (node->left)
        _avl_node_dump(node->left);
    printf("%d\n", node->value);
    if (node->right)
        _avl_node_dump(node->right);
}

void 
avl_dump(struct avl *avl) {
    printf("total %d nodes.\n\n", avl->count);
    _avl_node_dump(avl->root);
}
