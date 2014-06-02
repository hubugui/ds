#ifndef __AVL__
#define __AVL__

#ifdef __cplusplus
extern "C" {
#endif

struct avl;

/**
 * return 0: equal, -1: v1 less than v2, 1: v2 less than v1
 */
typedef int (*compare)(void *v1, void *v2);

struct avl *avl_new(void);
void avl_delete(struct avl *avl);

int avl_insert(struct avl *avl, void *value, compare cmp);
int avl_remove(struct avl *avl, void *value, compare cmp);

int avl_search(struct avl *avl, void *value, compare cmp);
int avl_max(struct avl *avl, void **value);
int avl_min(struct avl *avl, void **value);
void avl_in_order(struct avl *avl, void (*dump)(void *value));

#ifdef __cplusplus
}
#endif
#endif
