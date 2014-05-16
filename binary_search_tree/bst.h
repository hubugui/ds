#ifndef __BST__
#define __BST__

#ifdef __cplusplus
extern "C" {
#endif

struct bst;

struct bst *bst_new(void);
void bst_delete(struct bst *bst);

int bst_insert(struct bst *bst, int value);
int bst_remove(struct bst *bst, int value);

int bst_search(struct bst *bst, int value);
int bst_max(struct bst *bst);
int bst_min(struct bst *bst);
void bst_dump(struct bst *bst);

#ifdef __cplusplus
}
#endif
#endif
