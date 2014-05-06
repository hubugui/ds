#ifndef __BST__
#define __BST__

struct bst;

struct bst *bst_create();
void bst_destroy(struct bst *bst);

void bst_insert(struct bst *bst, int value);
void bst_delete(struct bst *bst, int value);

struct bst *bst bst_find(struct bst *bst, int value);
int bst_value(struct bst *bst);
int bst_min(struct bst *bst);
int bst_max(struct bst *bst);

#endif
