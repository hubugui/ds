#ifndef __AVL__
#define __AVL__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * non-recursion
 * non-thread safe
 * 64bits gcc
 */

struct avl;

/**
 * return value
 *
 * 0: equal
 * -1: v1 < v2
 * 1: v1 > v2
 */
typedef int (*compare)(void *v1, void *v2);
typedef void (*dump)(void *value);

struct avl *avl_new(void);
void avl_delete(struct avl *avl);
int avl_height(struct avl *avl);
unsigned int avl_count(struct avl *avl);

int avl_insert(struct avl *avl, void *value, compare cmp);
int avl_remove(struct avl *avl, void *value, compare cmp);

int avl_max(struct avl *avl, void **value);
int avl_min(struct avl *avl, void **value);
int avl_search(struct avl *avl, void *value, compare cmp);

/**
 * verify the legitimacy of the avl tree
 *
 * return value
 *
 * 0: suceess
 * -1: fail in node's height
 * -2: fail in node's parent point
 * -3: fail in node's value
 */
int avl_verify(struct avl *avl, compare cmp);

void avl_in_order(struct avl *avl, dump dmp);

/**
 * printf tree shape
 */
void avl_bfs_dump(struct avl *avl, dump dmp);

#ifdef __cplusplus
}
#endif
#endif
