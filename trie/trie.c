#include <ctype.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct trie_node {
    struct trie_node *childs[26];
    struct trie_node **parent;
    char leaf;
};

struct trie_search_box {
    struct trie_node **match_node, * *node;
    unsigned int string_len;
};

struct trie {
    struct trie_node *root;
    unsigned int string_count, node_count;
    struct trie_search_box sbox;
};

#define NODE_INDEX_OF_PARENT(n) ((int64_t) n - (int64_t) (*(*n)->parent)) / sizeof(struct trie_node *)
#define _trie_node_new() calloc(1, sizeof(struct trie_node))

static void
_trie_node_delete(struct trie_node *node) {
    if (node) {
        int i;

        for (i = 0; i < 26; i++) {
            _trie_node_delete(node->childs[i]);
        }
        free(node);
    }
}

struct trie *
trie_new(void) {
    struct trie *trie = calloc(1, sizeof(struct trie));

    if (trie) {
        trie->root = _trie_node_new();
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

unsigned int
trie_string_count(struct trie *trie) {
    return trie->string_count;
}

unsigned int
trie_node_count(struct trie *trie) {
    return trie->node_count;
}

int
trie_insert(struct trie *trie, const char *string) {
    int chr;
    struct trie_node **node;

    for (node = &trie->root; *string != '\0'; string++) {
        if (!isalpha(*string))
            goto fail;

        chr = tolower(*string) - 'a';
        if (!(*node)->childs[chr]) {
            if (!((*node)->childs[chr] = _trie_node_new()))
                goto fail;
            (*node)->childs[chr]->parent = node;
            trie->node_count++;
        }
        node = &(*node)->childs[chr];
    }
    if (node == &trie->root)
        goto fail;    
    (*node)->leaf = 1;
    trie->string_count++;
    return 0;
fail:
    /* notice, here don't delete parent node. hope to reuse when insert again. */
    return -1;
}

char *
trie_search(struct trie *trie,
            const char *string,
            char *result,
            unsigned int *result_size,
            struct trie *next_ptr) {
    struct trie_node **node;
    char *origin = result;
    int i, idx;

    if (trie) {
        /* find match string, save last node to box */
        memset(&trie->sbox, 0, sizeof(struct trie_search_box));
        for (node = &trie->root; *string; string++) {
            if (!isalpha(*string))
                goto fail;
            node = &(*node)->childs[(int) (tolower(*string) - 'a')];
            if (!(*node))
                goto fail;
            trie->sbox.match_node = trie->sbox.node = node;
            trie->sbox.string_len++;
            *result++ = *string;
        }
        if (trie->sbox.string_len == 0)
            goto fail;
        *result_size = trie->sbox.string_len;
        if ((*node)->leaf) {
            *result = '\0';
            return result;
        }
    } else {
        trie = next_ptr;
        result += *result_size;
    }

    node = trie->sbox.node;
    idx = 0;
loop:
    /* child */
    for (i = idx; i < 26; i++) {
        if ((*node)->childs[i]) {
            node = trie->sbox.node = &(*node)->childs[i];
            *result++ = i + 'a';
            *result_size += 1;
            if ((*node)->leaf) {
                *result = '\0';
                return origin;
            }
            idx = 0;
            goto loop;
        }
    }
    if (node == trie->sbox.match_node)
        goto fail;

    /* right brother */
    result--;
    *result_size -= 1;
    idx = NODE_INDEX_OF_PARENT(node) + 1;
    node = (*node)->parent;
    goto loop;
fail:
    return NULL;
}