#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "kuan_array.h"

struct kuan_array
{
    size_t size;
    size_t *value;
    char first;
};

struct kuan_array *kuan_array_new(size_t size)
{
    struct kuan_array *ka = calloc(1, sizeof(struct kuan_array));

    if (ka) {
        ka->size = size;
        ka->first = 1;
        ka->value = calloc(1, sizeof(size_t) * size);
        if (!ka->value) {
            free(ka);
            ka = NULL;
        }
    }
    return ka;
}

void kuan_array_delete(struct kuan_array *ka)
{
    free(ka->value);
    free(ka);
}

int kuan_array_next(struct kuan_array *ka, size_t *value)
{
    size_t i;

    for (i = 0; i < ka->size; i++) {
        if (ka->first) {
            ka->first = 0;
            break;
        } else {
            if (++ka->value[ka->size - i - 1] + 1 > ka->size) {
                ka->value[ka->size - i - 1] = 0;
            } else
                break;
        }
    }
    if (i == ka->size)
        return -1;

    memmove(value, ka->value, sizeof(size_t) * ka->size);
    return 0;
}