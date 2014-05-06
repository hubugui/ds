#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#include "dst.h"

struct bst
{
	struct bst *left;
	struct bst *right;
	int value;
};

struct bst *bst_create()
{
	return calloc(1, sizeof(struct bst));
}

void bst_destroy(struct bst *bst)
{
	if (bst)
	{
		if (bst->left)
			bst_destroy(bst->left);
		if (bst->right)
			bst_destroy(bst->right);
		free(bst);
	}
}

void bst_insert(struct bst *bst, int value)
{
	
}

void bst_delete(struct bst *bst, int value);

struct bst *bst bst_find(struct bst *bst, int value)
{
	if (bst)
	{
		if (bst->value > value)
			return bst_find(bst->left);
		if (bst->value < value)
			return bst_find(bst->right);
		return bst;
	}
	else
		return NULL;
}

int bst_value(struct bst *bst)
{
	return bst->value;
}

int bst_min(struct bst *bst)
{
	if (bst->left)
		return bst_min(bst->left);
	return bst->value;
}

int bst_max(struct bst *bst)
{
	if (bst->right)
		return bst_max(bst->right);
	return bst->value;
}
