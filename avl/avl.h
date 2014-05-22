#ifndef __AVL__
#define __AVL__

#ifdef __cplusplus
extern "C" {
#endif

struct avl;

struct avl *avl_new(void);
void avl_delete(struct avl *avl);

int avl_insert(struct avl *avl, int value);
int avl_remove(struct avl *avl, int value);

int avl_search(struct avl *avl, int value);
int avl_max(struct avl *avl);
int avl_min(struct avl *avl);
void avl_dump(struct avl *avl);

#ifdef __cplusplus
}
#endif
#endif
