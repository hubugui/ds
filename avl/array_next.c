#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_next.h"

struct array_next {
    size_t size;
    size_t *value;
};

struct array_next * 
array_next_new(size_t size) {
    struct array_next *an = calloc(1, sizeof(struct array_next));

    if (an) {
        an->size = size;
        an->value = calloc(1, sizeof(size_t) * size);
        if (!an->value) {
            free(an);
            an = NULL;
        }
    }
    return an;
}

void array_next_delete(struct array_next *an) {
    free(an->value);
    free(an);
}

int
array_next_next(struct array_next *an, size_t *value) {
    size_t i;

    for (i = 0; i < an->size; i++) {
        if (++an->value[an->size - i - 1] > an->size) {
            an->value[an->size - i - 1] = 0;
        } else
            break;
    }
    if (i == an->size)
        return -1;

    for (i = 0; i < an->size; i++) {
        value[i] = an->value[i];
    }
    return 0;
}