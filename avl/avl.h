#ifndef __AVL__
#define __AVL__

#ifdef __cplusplus
extern "C" {
#endif

struct avl;

typedef int (*cmpare)(void *v1, void *v2);

struct avl *avl_new(void);
void avl_delete(struct avl *avl);

void avl_set_cmp(struct avl *avl, compare cmp);
compare avl_get_cmp(struct avl *avl);

int avl_insert(struct avl *avl, void *value);
int avl_remove(struct avl *avl, void *value);

int avl_search(struct avl *avl, void *value);
int avl_max(struct avl *avl);
int avl_min(struct avl *avl);
void avl_in_order(struct avl *avl, void (*dump)(void *value));

#ifdef __cplusplus
}
#endif
#endif
