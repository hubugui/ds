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
_avl_node_search(struct avl *avl, void *value, struct avl_node ***target, compare cmp) {
    struct avl_node *node = avl->root;
    int rc;

    for (*target = &avl->root; node; node = **target) {
        rc = cmp(value, node->value);
        if (rc == 0)
            return node;
        if (rc < 0)
            *target = &node->left;
        else
            *target = &node->right;
    }
    return NULL;
}

int 
avl_search(struct avl *avl, void *value, compare cmp) {
    struct avl_node **target = NULL;
    return _avl_node_search(avl, value, &target, cmp) ? 0 : -1;
}

static struct avl_node *
_left_rotate(struct avl_node *node) {
   struct avl_note *child = node->right;

    if (child) {
        node->right = child->left;
        child->left = node;
    }
    return child;
}

static struct avl_node *
_right_rotate(struct avl_node *node) {
   struct avl_note *child = node->left;

    if (child) {
        node->left = child->right;
        child->right = node;
    }
    return child;
}

#define LEFT_HEIGHT(n)   ((n && n->left) ? n->left->height : 0)
#define RIGHT_HEIGHT(n)   ((n && n->right) ? n->right->height : 0)

static int 
_difference(struct avl_node *node) {
    return ;
}

int 
avl_insert(struct avl *avl, void *value, compare cmp) {
    struct avl_node *node, *rotate_node, **parent, **target;
    int rc;
    /* -1: left, 1: right, 0: invalid */
    int left_or_right[2];

    for (node = avl->root, parent = target = &avl->root, rotate_node = NULL;
        node != NULL;
        node = *target, parent = target) {
        if ((rc = cmp(value, node->value)) == 0)
            return 0;
        diff = LEFT_HEIGHT(node) - RIGHT_HEIGHT(node) - rc;
        target = rc < 0 ? &node->let : &node->right;
        if (ABS(diff) > 1) {
            rotate_node = node;
            left_or_right[0] = rc;
            left_or_right[1] = cmp(value, (*target)->value);
        }
    }
    if ((*target = _avl_node_new()))
        (*target)->value = value;
    else
        return -1;
    avl->count++;

    /* not balance */
    if (rotate_node) {
        if (left_or_right[0] == -1) {
            if (left_or_right[1] == 1)
                rotate_node->left = _left_rotate(rotate->left);
            *parent = _right_rotate(rotate_node);
        } else {
            if (left_or_right[1] == -1)
                rotate_node->right = _right_rotate(rotate->right);
            *parent = _left_rotate(rotate_node);
        }
    }
    return 0;
}

int 
avl_remove(struct avl *avl, void *value, compare cmp) {
    struct avl_node **target;
	struct avl_node *node = _avl_node_search(avl, value, &target);
   
    if (!node)
        return -1;

    if (!node->left && !node->right)
        *target = NULL;
    else if (!node->left || !node->right)
        *target = node->left ? node->left : node->right;
    else {
        /* right tree, min node */
        struct avl_node *min = node->right;
        struct avl_node **min_target = &node->right;

        while (min->left) {
            min_target = &min->left;
            min = min->left;
        }

        /* min remove from origin */
        *min_target = min->right;
        min->left = node->left;
        min->right = node->right;
        /* min insert to node's target */
        *target = min;
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
