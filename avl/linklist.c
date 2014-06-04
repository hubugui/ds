#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "linklist.h"

struct linklist_node {
    struct linklist_node *next;
    void *value;
    void *userdata1, *userdata2;
};

struct linklist {
    struct linklist_node *head, *tail;
    size_t size;
};

struct linklist;
struct linklist_node;

#define _linklist_node_new()	calloc(1, sizeof(struct linklist_node))

static struct linklist_node * 
_remove_head(struct linklist *list) {
    struct linklist_node *node, **parentp;

    for (node = list->head, parentp = &list->head; node; node = node->next) {
        *parentp = node->next;
        list->size--;
        if (list->tail == node)
            list->tail = NULL;
        break; 
    }
    return node; 
}

struct linklist * 
linklist_new(void) {
    return calloc(1, sizeof(struct linklist));
}

void linklist_delete(struct linklist *list) {
    struct linklist_node *node;

    while ((node = _remove_head(list))) {
        free(node);
    }
    free(list);
}

size_t 
linklist_size(struct linklist *list) {
    return list->size; 
}

int 
linklist_insert(struct linklist *list, void *value, void *userdata1, void *userdata2) {
    struct linklist_node *node = _linklist_node_new();

    if (node) {
        node->value = value;
        node->userdata1 = userdata1;
        node->userdata2 = userdata2;
        if (!list->head)
            list->head = node;
        if (list->tail)
            list->tail->next = node;
        list->tail = node;
        list->size++;
    }
    return node ? 0 : -1;
}

void * 
linklist_remove_head(struct linklist *list, void **userdata1_p, void **userdata2_p) {
    struct linklist_node *node = _remove_head(list);

    if (node) {
        *userdata1_p = node->userdata1;
        *userdata2_p = node->userdata2;
        return node->value;
    }
    return NULL;
}
