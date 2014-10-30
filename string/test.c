#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memmove.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

static void *
_simple_memmove(char *dst, const char *src, size_t size) {
    char *result = dst;

    if (dst <= src) {
        while (size--) {
            *dst++ = *src++;
        }
    } else {
        dst += size;
        src += size;
        while (size--) {
            *--dst = *--src;
        }
    }
    return result;
}

static int 
_test(const char *string, size_t dst_i, size_t src_i, size_t size) {
    char str1[256], str2[256];

    strcpy(str1, string);
    _simple_memmove(&str1[dst_i], &str1[src_i], size);

    strcpy(str2, string);
    _memmove(&str2[dst_i], &str2[src_i], size);
    return strcmp(str1, str2);
}

int
main(int argc, char **argv) {
    char *str = argv[1];
    size_t i, j, k, size, count = 0;

    if (!str)
        str = "0123456789abcdefghijklmnopqrstuvwxyz";
    size = strlen(str);

    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - 1; j++) {
            for (k = 0; k < size - MAX(i, j); k++) {
                count++;
                if (_test(str, i, j, k)) {
                    printf("\nfail in dst_i=%ld, src_i=%ld, size=%ld\n", i, j, k);
                    return -1;
                } else
                    printf("\r%ld case", count);
            }
        }
    }
    printf("\nsuccess!\n");
    return 0;
}
