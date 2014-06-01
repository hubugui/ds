#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

struct avl_node {
    struct avl_node *left, *right;
    int height;
    void *value;
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
_avl_node_search(struct avl *avl, void *value, struct avl_node ***parent, compare cmp) {
    struct avl_node *node = avl->root;
    int rc;

    for (*parent = &avl->root; node; node = **parent) {
        rc = cmp(value, node->value);
        if (rc == 0)
            return node;
        if (rc < 0)
            *parent = &node->left;
        else
            *parent = &node->right;
    }
    return NULL;
}

int 
avl_search(struct avl *avl, void *value, compare cmp) {
    struct avl_node **parent = NULL;
    return _avl_node_search(avl, value, &parent, cmp) ? 0 : -1;
}

static struct avl_node *
_left_rotate(struct avl_node *node) {
   struct avl_note *r = node->right;

    if (r) {
        node->right = r->left;
        r->left = node;
    }
    return r;
}

static struct avl_node *
_right_rotate(struct avl_node *node) {
   struct avl_note *r = node->left;

    if (r) {
        node->left = r->right;
        r->right = node;
    }
    return r;
}

static int 
_difference(struct avl_node *node) {
    if (node->left && node->right)
        return node->left->height - node->right->height;   
    if (node->left)
        return node->left->height;
    if (node->right)
        return node->right->height;
}

int 
avl_insert(struct avl *avl, void *value, compare cmp) {
    struct avl_node *node = avl->root;
    struct avl_node **parent = &avl->root;
    struct avl_node *rotate_node = NULL;
    int rc;

    while (node) {
        if ((rc = cmp(value, node->value)) == 0)
            return 0;
        diff = _difference(node);
        if (ABS(diff) > 1)
            rotate_node = node; 
        parent = rc < 0 ? &node->left : &node->right;
        node = *parent;
    }
    if ((*parent = _avl_node_new()))
        (*parent)->value = value;
    else
        return -1;
    avl->count++;

    /* not balance */
    if (rotate_node) {
         
    }
    return 0;
}

int 
avl_remove(struct avl *avl, void *value, compare cmp) {
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

void 
avl_in_order(struct avl *avl, void (*dump)(void *value)) {
    dump(avl->root->value);
}
