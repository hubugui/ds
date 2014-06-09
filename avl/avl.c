#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "avl.h"
#include "linklist.h"

struct avl_node {
    struct avl_node *left, *right, *parent;
    void *value;
    int height;
};

struct avl {
    struct avl_node *root;
    unsigned int count;
};

#define MAX(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
#define ABS(x)              (((x) < 0) ? -(x) : (x))

#define LEFT_HEIGHT(n)      (n->left ? 1 + n->left->height : 0)
#define RIGHT_HEIGHT(n)     (n->right ? 1 + n->right->height : 0)
#define DIFF_HEIGHT(n)      (LEFT_HEIGHT(n) - RIGHT_HEIGHT(n))
#define HEIGHT(n)           (MAX(LEFT_HEIGHT(n), RIGHT_HEIGHT(n)))
#define SET_HEIGHT(n)       (n->height = HEIGHT(n))

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

int 
avl_height(struct avl *avl) {
    if (avl->root)
        return avl->root->height;
    return 0; 
}

static struct avl_node *  
_node_search(struct avl *avl, void *value, struct avl_node ***parentp, compare cmp) {
    struct avl_node *node;
    int rc;

    for (node = avl->root, *parentp = &avl->root; 
        node != NULL; 
        node = **parentp) {
        if ((rc = cmp(value, node->value)) == 0)
            return node;
        *parentp = rc < 0 ? &node->left : &node->right;
    }
    return NULL;
}

int 
avl_search(struct avl *avl, void *value, compare cmp) {
    struct avl_node **parentp = NULL;
    return _node_search(avl, value, &parentp, cmp) ? 0 : -1;
}

static struct avl_node *
_left_rotate(struct avl_node *node) {
   struct avl_node *child = node->right;

    if (child) {
        child->parent = node->parent;
        node->right = child->left;
        if (node->right)
            node->right->parent = node;
        node->parent = child;
        child->left = node;        
        SET_HEIGHT(node);
        SET_HEIGHT(child);
    }
    return child;
}

static struct avl_node *
_right_rotate(struct avl_node *node) {
   struct avl_node *child = node->left;

    if (child) {
        child->parent = node->parent;
        node->left = child->right;
        if (node->left)
            node->left->parent = node;
        node->parent = child;
        child->right = node;
        SET_HEIGHT(node);
        SET_HEIGHT(child);
    }
    return child;
}

static void 
_avl_rebalance(struct avl *avl, struct avl_node *node, compare cmp) {
    struct avl_node *leaf, **parentp;

    for (leaf = node, node = node->parent; node != NULL; node = node->parent) {
        /* parent height no change means tree balance still */
        if (node->height == HEIGHT(node))
            return;
        SET_HEIGHT(node);

        /* balance */
        if (ABS(DIFF_HEIGHT(node)) > 1) {
            if (node->parent)
                parentp = (node == node->parent->left) ? &node->parent->left : &node->parent->right;
            else
                parentp = &avl->root;
            if (cmp(leaf->value, node->value) == -1) {                    
                if (cmp(leaf->value, node->left->value) == 1)
                    node->left = _left_rotate(node->left);
                *parentp = _right_rotate(node);
            } else {
                if (cmp(leaf->value, node->right->value) == -1)
                    node->right = _right_rotate(node->right);
                *parentp = _left_rotate(node);
            }
            SET_HEIGHT((*parentp));
            break;
        }
    }
}

int 
avl_insert(struct avl *avl, void *value, compare cmp) {
    struct avl_node *node, *parent, **parentp;
    int rc; 

    for (node = avl->root, parent = NULL, parentp = &avl->root;
        node != NULL;
        parent = node, node = (*parentp)) {
        if ((rc = cmp(value, node->value)) == 0)
            return 0;
        parentp = rc < 0 ? &node->left : &node->right;
    }
    if ((*parentp = _avl_node_new())) {
        (*parentp)->value = value;
        (*parentp)->parent = parent;
        if (parent)
            _avl_rebalance(avl, *parentp, cmp);
        avl->count++;
    } else
        return -1;
    return 0;
}

int 
avl_remove(struct avl *avl, void *value, compare cmp) {
    return 0;
}

int 
avl_max(struct avl *avl, void **value) {
    struct avl_node *node = avl->root;

    if (node) {
    	while (node->right)
            node = node->right;
        *value = node->value;
        return 0;
    }
    return -1;
}

int 
avl_min(struct avl *avl, void **value) {
    struct avl_node *node = avl->root;

    if (node) {
    	while (node->left)
            node = node->left;
        *value = node->value;
        return 0;
    }
    return -1;
}

static int 
_in_order_visit(struct avl_node *node, int (*visit)(struct avl_node *node)) {
    if (node) {
        int rc;

        if ((rc = _in_order_visit(node->left, visit)))
            return rc;
        if ((rc = visit(node)))
            return rc;
        if ((_in_order_visit(node->right, visit)))
            return rc;
    }
    return 0;
}

int 
_node_verify(struct avl_node *node) {
    if (ABS(DIFF_HEIGHT(node)) > 1)
        return -1;
    if (node->parent) {
        if (node == node->parent->left || node == node->parent->right)
            return 0;
        else
            return -2;
    }
    return 0;
}

int 
avl_verify(struct avl *avl) {
    return _in_order_visit(avl->root, _node_verify);
}

static void 
_in_order(struct avl_node *node, dump dmp) {
    if (node->left)
        _in_order(node->left, dmp);
    dmp(node->value);
    if (node->right)
        _in_order(node->right, dmp);
}

void 
avl_in_order(struct avl *avl, dump dmp) {
    _in_order(avl->root, dmp);
}

void 
avl_bfs(struct avl *avl, bfs_dump dmp) {
    struct avl_node *node = avl->root;
    struct linklist *list;
    long long int depth = 0, idx = 0, tmp = 0;
    int height = avl_height(avl);

    if (!node)
        return;

    if ((list = linklist_new()) == NULL)
        return;

    if (linklist_insert(list, node, (void *) depth, NULL))
        goto fail;

    while (linklist_size(list) > 0) {
        node = (struct avl_node *) linklist_remove_head(list, (void **) &depth, (void **) &tmp);

        if (node)
            dmp(node->value, depth, idx);
        if (linklist_insert(list, node ? node->left : NULL, (void *) depth+1, NULL))
            goto fail;
        if (linklist_insert(list, node ? node->right : NULL, (void *) depth+1, NULL))
            goto fail;
        if (idx + 1 == (long long int) pow(2, height+1))
           break; 
        idx++;
    }

fail:
    linklist_delete(list);
}
