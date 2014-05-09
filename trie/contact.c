#include <stdio.h>
#include "trie.h"

int 
main(int argc, char **argv) {
	int i;
	char result[1024], *string;
	unsigned int result_size = 0;
	struct trie *t = trie_new();

	if (!t) {
		printf("trie_new() fail\n");
		return -1;
	}

	for (i = 1; i < argc - 1; i++) {
		if (trie_insert(t, argv[i])) {
			printf("fail\n");
			goto fail;
		}
	}

	printf("total string count=%d\n", trie_string_count(t));
	printf("total node count=%d\n", trie_node_count(t));
	printf("\nsearching '%s':\n", argv[argc - 1]);

	string = trie_search(t, argv[argc - 1], result, &result_size, NULL);
	for (i = 0; string; i++) {
		printf("%02d:'%s', len=%d\n", i+1, result, result_size);
		string = trie_search(NULL, argv[argc - 1], result, &result_size, t);
	}

	printf("\n%d results\n", i);
fail:
	trie_delete(t);
	return 0;
}
