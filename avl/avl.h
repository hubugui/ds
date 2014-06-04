#ifndef __AVL__
#define __AVL__

#ifdef __cplusplus
extern "C" {
#endif

/*
 * not recursion
 * not thread safe
 */

struct avl;

/**
 * return 0: equal, -1: v1 < v2, 1: v2 > v1
 */
typedef int (*compare)(void *v1, void *v2);
typedef void (*dump)(void *value);
typedef void (*bfs_dump)(void *value, long long int depth, long long int idx);

struct avl *avl_new(void);
void avl_delete(struct avl *avl);
int avl_height(struct avl *avl);

int avl_insert(struct avl *avl, void *value, compare cmp);
int avl_remove(struct avl *avl, void *value, compare cmp);

int avl_search(struct avl *avl, void *value, compare cmp);
int avl_max(struct avl *avl, void **value);
int avl_min(struct avl *avl, void **value);
int avl_verify(struct avl *avl);

void avl_in_order(struct avl *avl, dump dmp);
void avl_bfs(struct avl *avl, bfs_dump dmp);

#ifdef __cplusplus
}
#endif
#endif
