#ifndef __TRIE_H__
#define __TRIE_H__

#ifdef __cplusplus
extern "C" {
#endif

struct trie;

struct trie *trie_create(void);
void trie_delete(struct trie *trie);

int trie_insert(struct trie *trie, const char *string);
char *trie_search(struct trie *trie, const char *string, char *result, struct trie *next_ptr);

#ifdef __cplusplus
}
#endif
#endif
