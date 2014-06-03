#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "linklist.h"

struct linklist_node {
    struct linklist_node *next;
    void *value;
};

struct linklist {
    struct linklist_node *head, *tail;
    unsigned int count;
};

struct linklist;
struct linklist_node;

#define _linklist_node_new()	calloc(1, sizeof(struct linklist_node))

static struct linklist_node * 
_remove_head(struct linklist *list) {
    struct linklist_node *node, **parentp;

    for (node = list->head, parentp = &list->head; node; node = node->next) {
        *parentp = node->next;
        list->count--;
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

int 
linklist_insert(struct linklist *list, void *value) {
    struct linklist_node *node = _linklist_node_new();

    if (node) {
        node->value = value;
        if (!list->head)
            list->head = node;
        if (list->tail)
            list->tail->next = node;
        list->tail = node;
        list->count++;
    }
    return node ? 0 : -1;
}

void * 
linklist_remove_head(struct linklist *list) {
    struct linklist_node *node = _remove_head(list);

    if (node)
        return node->value;
    return NULL;
}
