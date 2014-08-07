#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "avl.h"
#include "linklist.h"

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

#define _avl_node_new() calloc(1, sizeof(struct avl_node))

struct avl_node
{
    struct avl_node *left, *right, *parent;
    void *value;
    int height;
};

struct avl
{
    struct avl_node *root;
    unsigned int count;
};

static void _avl_node_delete(struct avl_node *node)
{
    if (node->left)
        _avl_node_delete(node->left);
    if (node->right)
        _avl_node_delete(node->right);
    free(node);
}

struct avl *avl_new(void)
{
    return calloc(1, sizeof(struct avl));
}

void avl_delete(struct avl *avl)
{
    if (avl->root)
        _avl_node_delete(avl->root);
    free(avl);
}

int avl_height(struct avl *avl)
{
    return avl->root ? avl->root->height : 0;
}

unsigned int avl_count(struct avl *avl)
{
    return avl->count;
}

static struct avl_node *_node_search(struct avl *avl, void *value, struct avl_node ***parentp, compare cmp)
{
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

static struct avl_node *_left_rotate(struct avl_node *node)
{
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

static struct avl_node *_right_rotate(struct avl_node *node)
{
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

static void _insert_rebalance(struct avl *avl, struct avl_node *node, compare cmp)
{
    struct avl_node *leaf, **parentp;

    for (leaf = node, node = node->parent; node != NULL; node = node->parent) {
        /* parent height no change means tree balance still */
        if (node->height == HEIGHT(node))
            return;
        SET_HEIGHT(node);

        /* rebalance */
        if (ABS(DIFF_HEIGHT(node)) > 1) {
            if (node->parent)
                parentp = (node == node->parent->left) ? 
                        &node->parent->left : &node->parent->right;
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

int avl_insert(struct avl *avl, void *value, compare cmp)
{
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
            _insert_rebalance(avl, *parentp, cmp);
        avl->count++;
    } else
        return -1;
    return 0;
}

static void _swap_value(struct avl_node *node1, struct avl_node *node2)
{
    void *value = node1->value;
    node1->value = node2->value;
    node2->value = value;
}

static void _remove_rebalance(struct avl *avl, struct avl_node *node, compare cmp)
{
    struct avl_node **parentp;

    for (parentp = NULL; node != NULL; node = node->parent) {
retry:
        SET_HEIGHT(node);
        /* rebalance */
        if (ABS(DIFF_HEIGHT(node)) > 1) {
            if (node->parent)
                parentp = (node == node->parent->left) ? 
                        &node->parent->left : &node->parent->right;
            else
                parentp = &avl->root;
            /* left height > right height */
            if (DIFF_HEIGHT(node) > 0) {
                if (node->left->right)
                    node->left = _left_rotate(node->left);
                *parentp = _right_rotate(node);
                node = (*parentp)->left;
            } else {
                if (node->right->left)
                    node->right = _right_rotate(node->right);
                *parentp = _left_rotate(node);
                node = (*parentp)->right;
            }
            SET_HEIGHT((*parentp));
            goto retry;
        }
    }
}

int avl_remove(struct avl *avl, void *value, compare cmp)
{
    struct avl_node *node, **parentp, *min, *left;

    if ((node = _node_search(avl, value, &parentp, cmp)) == NULL)
        return -1;

retry:
    /* leaf */
    if (!node->left && !node->right) {
        *parentp = NULL;
        goto rebalance;
    }
    /* single child */
    if (!node->left || !node->right) {
        *parentp = node->left ? node->left : node->right;
        (*parentp)->parent = node->parent;
        goto rebalance;
    }
    /* double child, find the min node from right subtree */
    for (left = node->right; left; left = min->left) {
        min = left;
    }
    _swap_value(node, min);
    /* now node only have 0 or 1 child */
    node = min;
    parentp = (node == node->parent->left) ?
              &node->parent->left : &node->parent->right;
    goto retry;

rebalance:
    _remove_rebalance(avl, node->parent, cmp);
    avl->count--;
    free(node);
    return 0;
}

int avl_max(struct avl *avl, void **value)
{
    struct avl_node *node = avl->root;

    if (node) {
        while (node->right)
            node = node->right;
        *value = node->value;
        return 0;
    }
    return -1;
}

int avl_min(struct avl *avl, void **value)
{
    struct avl_node *node = avl->root;

    if (node) {
        while (node->left)
            node = node->left;
        *value = node->value;
        return 0;
    }
    return -1;
}

int avl_search(struct avl *avl, void *value, compare cmp)
{
    struct avl_node **parentp = NULL;
    return _node_search(avl, value, &parentp, cmp) ? 0 : -1;
}

static int _in_order(struct avl_node *node, 
                    int (*visit)(struct avl_node *node, void *userdata), 
                    void *userdata)
{
    if (node) {
        int rc;

        if ((rc = _in_order(node->left, visit, userdata)))
            return rc;
        if ((rc = visit(node, userdata)))
            return rc;
        if ((_in_order(node->right, visit, userdata)))
            return rc;
    }
    return 0;
}

static int _node_verify(struct avl_node *node, void *userdata)
{
    compare cmp = (compare) userdata;

    if (ABS(DIFF_HEIGHT(node)) > 1)
        return -1;
    if (node->parent)
        return (node == node->parent->left || node == node->parent->right) 
                ? 0 : -2;
    if (node->left && cmp(node->left->value, node->value) > 0)
        return -3;
    if (node->right && cmp(node->value, node->right->value) > 0)
        return -3;
    return 0;
}

int avl_verify(struct avl *avl, compare cmp)
{
    return _in_order(avl->root, _node_verify, cmp);
}

static int _node_dump(struct avl_node *node, void *userdata)
{
    dump dmp = (dump) userdata;
    dmp(node->value);
    return 0;
}

void avl_in_order(struct avl *avl, dump dmp)
{
    _in_order(avl->root, _node_dump, dmp);
}

static void _node_bfs_dump(void *value, 
                            int depth, 
                            int idx, 
                            int height,
                            dump dmp,
                            int *pre_depth,
                            int *pre_idx_line)
{
    int i, idx_line = idx - ((( int) pow(2, depth)) - 1);
    int pow_unit = (int) pow(2, height - depth);
    char *unit = "  ";

    int left_unit = pow_unit - 1;
    int node_unit = 2 * pow_unit - 1;

    /* formatter */
    if (depth == (*pre_depth)) {
        for (i = 0; i < (idx_line - *pre_idx_line) * (1 + node_unit) - 1; i++) {
           printf("%s", unit);
        }
    } else {
        if (depth > 0)
            printf("\n");
        for (i = 0; i < left_unit; i++) {
            printf("%s", unit);
        }
        for (i = 0; i < idx_line * (1+node_unit); i++) {
            printf("%s", unit);
        }
    }
    *pre_idx_line = idx_line;
    *pre_depth = depth;

    dmp(value);    
}

void avl_bfs_dump(struct avl *avl, dump dmp)
{
    struct avl_node *node = avl->root;
    struct linklist *list;
    int depth = 0, idx = 0, tmp = 0;
    int pre_depth = -1, pre_idx_line = -1;
    int height = avl_height(avl);

    if (!node)
        return;
    if ((list = linklist_new()) == NULL)
        return;

    if (linklist_insert(list, node, (void *) (long int) depth, NULL))
        goto fail;

    while (linklist_size(list) > 0) {
        node = (struct avl_node *) linklist_remove_head(list, 
                                                        (void **) &depth, 
                                                        (void **) &tmp);

        if (node)
            _node_bfs_dump(node->value, depth, idx, 
                            height,  
                            dmp,
                            &pre_depth, &pre_idx_line);
        if (linklist_insert(list, node ? node->left : NULL, 
                            (void *) (long int) (depth + 1), NULL))
            goto fail;
        if (linklist_insert(list, node ? node->right : NULL, 
                            (void *) (long int) (depth + 1), NULL))
            goto fail;
        if (idx + 1 == (int) pow(2, height + 1))
            break;
        idx++;
    }

    printf("\n");
fail:
    linklist_delete(list);
}