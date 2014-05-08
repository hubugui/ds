#include <memory.h>
#include <stdio.h>

struct trie_node {
	struct trie_node *childs[26];
	struct trie_node *parent;
	char leaf;
};

struct trie {
	struct trie_node *root;
	unsigned int string_count, node_count;
	struct trie_search_box sbox;
};

static struct trie_node *
_trie_node_create(void) {
	return calloc(1, sizeof(struct trie_node));
}

static void 
_trie_node_delete(struct trie_node *node) {
	if (node) {
		for (int i = 0; i < 26; i++) {
			_trie_node_delete(node->childs[i]);
		}
		free(node);
	}
}

struct trie *
trie_create(void) {
	struct trie *trie = calloc(1, sizeof(struct trie));

	if (trie) {
		trie->root = _trie_node_create();
		if (!trie->root) {
			free(trie);
			trie = NULL;
		}
	}
	return trie;
}

void 
trie_delete(struct trie *trie) {
	_trie_node_delete(trie->root);
	free(trie);
}

int 
trie_insert(struct trie *trie, const char *string) {
	for (char chr = *string, struct trie_node *node = trie->root; chr != '\0'; string++) {
		if (!isalpha(chr))
			goto fail;

		chr = tolower(chr) - 'a';
		if (!node->childs[chr]) {
			if (!(node->childs[chr] = _trie_node_create()))
				goto fail;
			node->childs[chr]->parent = node;
			trie->node_count++;
		}
		node = node->childs[chr];	
	}
	if (node == trie->root)
		goto fail;
	node->leaf = 1;
	trie->string_count++;
	return 0;
fail:
	/* notice, here don't delete parent node. hope to reuse when insert again. */
	return -1;
}

struct trie_search_box {
	const char *string, *origin;
	struct trie_node **match_node, **node;
	unsigned int string_len;
};

#define NODE_INDEX_OF(n) ((int) n - (int) (*n)->parent) / sizeof(struct trie_node *);

static struct trie_node ** 
_trie_search_next(struct trie *trie) {
	/* child */
	for (i = 0; i < 26; i++) {
		if (node->childs[i]) {
			trie->sbox.node = &node->childs[i];
			break;
		}
	}
	/* right brother */
	if (i == 26) {
		int j = NODE_INDEX_OF(trie->sbox.node);

		while () {
			node = node->parent;
			for (i = j+1; i < 26; i++) {
				if (node->childs[i]) {
					trie->sbox.node = node->childs[i];
					break;
				}
			}
		}
	}
	return origin;
}

char * 
trie_search(struct trie *trie, const char *string, char *result, struct trie *next_ptr) {
	struct trie_node **node;
	char *origin;

	if (trie) {
		for (origin = (char *) string, node = &trie->root; *string; string++) {
			if (!isalpha(*string))
				goto fail;
			node = &node->childs[tolower(*string) - 'a'];
			if (!(*node))
				goto fail;
			trie->sbox.match_node = trie->sbox.node = node; 
		}
		trie->sbox.string_len = (unsigned int) (string - origin);
		if (trie->sbox.string_len == 0)
			goto fail;
	} else
		trie = next_ptr;

	strcpy(result, string);
	origin = result;
	result += trie->sbox.string_len - 1;
loop:
	/* end */
	if ((node = trie->sbox.node)) {
		trie->sbox.node = _trie_search_next(trie, &result);
		*result++ = 'a' + NODE_INDEX_OF(node);
		if ((*node)->leaf)
			return origin;
		goto loop;
	}
fail:
	memset(&trie->sbox, 0, sizeof(struct trie_search_box));
	return NULL;
}
