#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memmove.h"

int
main(int argc, char **argv) {
    char array[64];
    char *string = array;
    char *dst = string;
    char *src = &string[2];
    
    printf("%d\n", sizeof(size_t));
    printf("%d\n", sizeof(long long));

    strcpy(array, "12345678");

    _memmove(dst, src, 5);
    printf("dst=%s, src=%s, size=%d\n", dst, src, 5);

    strcpy(array, "12345678");
    dst = string + 2;
    src = string;
    _memmove(dst, src, 5);
    printf("dst=%s, src=%s, size=%d\n", dst, src, 5);

    strcpy(array, "12345678");
    dst = string + 2;
    src = string;
    _memmove(dst, src, 5);
    printf("dst=%s, src=%s, size=%d\n", dst, src, 5);
    return 0;
}
