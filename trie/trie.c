#include <memory.h>
#include <stdio.h>

struct trie_node {
	struct trie_node *childs[26];
	char leaf;
};

struct trie {
	struct trie_node *root;
	unsigned int string_count, node_size, leaf_size;
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
		chr = tolower(chr) - 'a';

		if (!node->childs[chr]) {
			if (node->childs[chr] = _trie_node_create())
				trie->node_count++;
			else
				/* notice, here don't delete parent node. hope to reuse when insert again. */
				return -1;
		}
		node = node->childs[chr];	
	}
	
	if (!node->leaf)
		trie->leaf_count++;
	node->leaf = 1;
	trie->string_count++;
	return 0;
}

struct trie_search_box {
	const char *string, *origin;
	struct trie_node *prefix_node, *node;
	int child_index;
	unsigned int string_len;
};

static char * 
_trie_search_recursion(struct trie *trie, const char *string, char *result, struct trie_node *node) {
	char *origin = result;
	int i;

	/* -1 mark need to check that current node is not leaf */
	if (trie->sbox.child_index == -1) {
		trie->sbox.child_index = 0;
		if (node->leaf)
			return origin;
	}

	/* child */
	result += trie->sbox.string_len;
	for (i = trie->sbox.child_index; i < 26; i++) {
		struct trie_node *child = node[i];

		if (child) {
			*result++ = i + 'a';
			trie->sbox.child_index = -1;
			return _trie_search_recursion(trie, string, result, child);		
		}
	}
	return NULL;
}

char * 
trie_search(struct trie *trie, const char *string, char *result, struct trie *next_ptr) {
	if (trie) {
		const char *origin = string;

		for (struct trie_node *node = trie->root; *string; string++) {
			if (!isalpha(*string))
				goto fail;
			node = node->childs[tolower(*string) - 'a'];
			if (!node)
				goto fail;
			trie->sbox.prefix_node = trie->sbox.node = node;
		}
		trie->sbox.string_len = (unsigned int) (string - origin);
		if (trie->sbox.string_len == 0)
			goto fail;
		trie->sbox.child_index = -1; 
	} else
		trie = next_ptr;

	strcpy(result, string);
	return _trie_search_recursion(trie, string, result);
fail:
	memset(&trie->sbox, 0, sizeof(struct trie_search_box));
	return NULL;
}
