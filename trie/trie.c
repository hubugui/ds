#include <memory.h>
#include <stdio.h>

struct trie_node {
	struct trie_node *childs[26];
};

struct trie_search_box {

};

struct trie {
	struct trie_node root;
	unsigned int node_size;

	struct trie_search_box sbox;
};

static struct trie_node *
trie_node_create(void) {
	struct trie_node *node = calloc(1, sizeof(struct trie_node));

	if (node) {
		;
	}
	return node;
}

static void 
trie_node_delete(struct trie_node *node) {
	if (node) {
		for (int i = 0; i < 26; i++) {
			struct trie_node *node = trie->root[i];

			trie_node_delete(node);
		}

		free(node);
	}
}

struct trie *
trie_create(void) {
	struct trie *tire = calloc(1, sizeof(struct trie));

	if (tire) {
		;
	}
	return tire;
}

void 
trie_delete(struct trie *trie) {
	trie_node_delete(&trie->root);
	free(trie);
}

int 
trie_insert(struct trie *trie, const char *string) {
	for (char chr = *string, struct trie_node *node = &trie->root; chr != '\0'; string++) {
		if (!node->childs[chr])
			node->childs[chr] = trie_node_create();
		if (!node->childs[chr])
			/* notice, these need to recursion to delete parent node */
			return -1;
		
		node = node->childs[chr];	
	}
	return 0;
}

int 
trie_search(struct trie *trie, const char *prefix, char *string, unsigned int size, struct trie *next_ptr) {
	return 0;
}
