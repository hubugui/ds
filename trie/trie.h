#ifndef __TRIE_H__
#define __TRIE_H__

#ifdef __cplusplus
extern "C" {
#endif

struct trie;

struct trie *trie_new(void);
void trie_delete(struct trie *trie);

int trie_insert(struct trie *trie, const char *string);
char *trie_search(struct trie *trie, const char *string, char *result, unsigned int *result_size, struct trie *next_ptr);

unsigned int trie_string_count(struct trie *trie);
unsigned int trie_node_count(struct trie *trie);

#ifdef __cplusplus
}
#endif
#endif
